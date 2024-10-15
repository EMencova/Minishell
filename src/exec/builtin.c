/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:20:02 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 18:38:55 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int					g_exit_status;

int	pipe_builtin(t_shell *shell, t_list *cmd_ls, int *exit, int len)
{
	char	**args;
	int		builtin_result;

	while (cmd_ls)
	{
		args = ((t_exec *)cmd_ls->content)->args;
		len = ft_strlen(*args);
		if (args && !ft_strncmp(args[0], "exit", 4) && len == 4)
			return (g_exit_status = m_exit(shell, cmd_ls, exit));
		else if (*args && !ft_strncmp(args[0], "cd", 2) && len == 2)
			return (g_exit_status = m_cd(shell));
		else if (!cmd_ls->next && args && !ft_strncmp(args[0], "export", 6))
			return (g_exit_status = m_export(shell));
		else if (!cmd_ls->next && args)
		{
			builtin_result = handle_basic_builtins(shell, args);
			if (builtin_result != -1)
				return (g_exit_status = builtin_result);
		}
		cmd_ls = cmd_ls->next;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (g_exit_status);
}

char	*cmd_find(char **path_env, char *comnd, char *path_full)
{
	char	*tmp;
	int		i;

	i = -1;
	path_full = NULL;
	while (path_env && path_env[++i])
	{
		tmp = ft_strjoin(path_env[i], "/");
		if (!tmp)
			return (NULL);
		path_full = ft_strjoin(tmp, comnd);
		free(tmp);
		if (!path_full)
			return (NULL);
		if (access(path_full, F_OK) == 0)
			return (path_full);
		free(path_full);
		path_full = NULL;
	}
	return (NULL);
}

int	handle_basic_builtins(t_shell *shell, char **args)
{
	if (!ft_strncmp(args[0], "pwd", 3))
		return (g_exit_status = m_pwd());
	else if (!ft_strncmp(args[0], "echo", 4))
		return (g_exit_status = m_echo(args));
	else if (!ft_strncmp(args[0], "unset", 5))
		return (g_exit_status = m_unset(shell));
	else if (!ft_strncmp(args[0], "env", 3))
		return (g_exit_status = m_env(shell, args));
	else if (!ft_strncmp(args[0], "expr", 4))
		return (g_exit_status = m_expr(args));
	return (-1);
}

int	builtin(t_shell *shell, t_list *cmd_ls, int *exit, int len)
{
	char	**args;
	int		builtin_result;

	while (cmd_ls)
	{
		args = ((t_exec *)cmd_ls->content)->args;
		len = ft_strlen(*args);
		if (args && !ft_strncmp(args[0], "exit", 4) && len == 4)
			return (g_exit_status = m_exit(shell, cmd_ls, exit));
		else if (*args && !ft_strncmp(args[0], "cd", 2) && len == 2)
			return (g_exit_status = m_cd(shell));
		else if (!cmd_ls->next && args && !ft_strncmp(args[0], "export", 6))
			return (g_exit_status = m_export(shell));
		else if (!cmd_ls->next && args)
		{
			builtin_result = handle_basic_builtins(shell, args);
			if (builtin_result != -1)
				return (g_exit_status = builtin_result);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		cmd_execute(shell, cmd_ls);
		cmd_ls = cmd_ls->next;
	}
	return (g_exit_status);
}

int	built_check(t_exec *cmd)
{
	int	i;

	if (!cmd->args)
		return (0);
	if ((cmd->args && ft_strchr(*cmd->args, '/'))
		|| (cmd->args && ft_strchr((const char *)cmd->args, '/')))
		return (0);
	i = ft_strlen(*cmd->args);
	if (!ft_strncmp(*cmd->args, "pwd", i) && i == 3)
		return (1);
	if (!ft_strncmp(*cmd->args, "env", i) && i == 3)
		return (1);
	if (!ft_strncmp(*cmd->args, "cd", i) && i == 2)
		return (1);
	if (!ft_strncmp(*cmd->args, "export", i) && i == 6)
		return (1);
	if (!ft_strncmp(*cmd->args, "unset", i) && i == 5)
		return (1);
	if (!ft_strncmp(*cmd->args, "echo", i) && i == 4)
		return (1);
	if (!ft_strncmp(*cmd->args, "exit", i) && i == 4)
		return (1);
	if (!ft_strncmp(*cmd->args, "env", i) && i == 3)
		return (1);
	return (0);
}
