/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:45:14 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 20:55:37 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../../minishell.h"
#include <dirent.h>

static DIR	*check_cmd(t_shell *shell, t_list *comnd, char ***str)
{
	t_exec	*node;
	DIR		*directory;
	char	*path_env;

	directory = NULL;
	node = comnd->content;
	if (node && node->args)
		directory = opendir((const char *)node->args);
	if (node && node->args && ft_strchr(*node->args, '/') && !directory)
	{
		*str = ft_split(*node->args, '/');
		node->path = ft_strdup(*node->args);
		free(node->args[0]);
		node->args[0] = ft_strdup(str[0][form_len(*str) - 1]);
	}
	else if (!built_check(node) && node && node->args && !directory)
	{
		path_env = get_env("PATH", shell->keys, 4);
		*str = ft_split(path_env, ':');
		if (!*str)
			m_error(ERR_PIPE, "Failed to split PATH", 127);
		free(path_env);
		node->path = cmd_find(*str, *node->args, node->path);
	}
	return (directory);
}

int	handle_builtin_commands(t_shell *shell, t_exec *node, t_list *comnd)
{
	if (built_check(node))
	{
		if (node->out != STDOUT_FILENO)
			dup2(node->out, STDOUT_FILENO);
		pipe_builtin(shell, comnd, &g_exit_status, ft_strlen(node->args[0]));
		return (1);
	}
	return (0);
}

int	check_directory(t_shell *shell, t_list *comnd, char ***str, t_exec *node)
{
	DIR	*directory;

	directory = check_cmd(shell, comnd, str);
	if (directory)
	{
		closedir(directory);
		m_error(ERR_ISDIR, node->args[0], 126);
		return (1);
	}
	return (0);
}
/*
void	fork_and_execute(t_shell *shell, t_exec *node)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		m_error(ERR_FORK, "Fork failed", 1);
		return;
	}
	else if (pid == 0)
	{
		if (node->in != STDIN_FILENO)
			dup2(node->in, STDIN_FILENO);
		if (node->out != STDOUT_FILENO)
			dup2(node->out, STDOUT_FILENO);

		execve(node->path, node->args, shell->keys);
		m_error(ERR_NEWCMD, node->args[0], 126);
		exit(126);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}*/

void	fork_and_execute(t_shell *shell, t_exec *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid < 0)
	{
		m_error(ERR_FORK, "Fork failed", 1);
		return ;
	}
	if (pid == 0)
	{
		if (node->in != STDIN_FILENO)
			dup2(node->in, STDIN_FILENO);
		if (node->out != STDOUT_FILENO)
			dup2(node->out, STDOUT_FILENO);
		execve(node->path, node->args, shell->keys);
		m_error(ERR_NEWCMD, node->args[0], 126);
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

void	command_get_redir_left(t_shell *shell, t_list *comnd)
{
	t_exec	*node;
	int		original_stdout;
	int		original_stdin;
	char	**str;

	node = comnd->content;
	str = NULL;
	node = comnd->content;
	duplicate_file_descriptors(&original_stdout, &original_stdin);
	if (!handle_builtin_commands(shell, node, comnd)
		&& !check_directory(shell, comnd, &str, node)
		&& node->path && access(node->path, X_OK) == 0)
	{
		cleanup_redirection_tokens(node);
		fork_and_execute(shell, node);
	}
	else if (!node->path || access(node->path, X_OK) != 0)
		m_error(ERR_NEWCMD, node->args[0], 126);
	close(node->out);
	if (node->in != STDIN_FILENO)
		close(node->in);
	restore_file_descriptors(original_stdout, original_stdin);
}
