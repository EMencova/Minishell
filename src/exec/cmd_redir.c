/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:55:44 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 21:02:59 by emencova         ###   ########.fr       */
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

void	execute_builtin_command(t_shell *shell, t_exec *node, t_list *comnd)
{
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	if (node->out != STDOUT_FILENO)
		dup2(node->out, STDOUT_FILENO);
	pipe_builtin(shell, comnd, &g_exit_status, ft_strlen(node->args[0]));
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	close(node->out);
}

void	handle_command_execution(t_shell *shell, t_exec *node)
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
	else if (pid == 0)
	{
		if (node->out != STDOUT_FILENO)
			dup2(node->out, STDOUT_FILENO);
		execve(node->path, node->args, shell->keys);
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

void	execute_external_command(t_shell *shell, t_list *comnd)
{
	t_exec	*node;
	char	**str;
	DIR		*directory;

	directory = check_cmd(shell, comnd, &str);
	node = comnd->content;
	str = NULL;
	if (directory)
	{
		closedir(directory);
		m_error(ERR_ISDIR, node->args[0], 126);
		return ;
	}
	if (node->path && access(node->path, X_OK) == 0)
		handle_command_execution(shell, node);
	else
		m_error(ERR_NEWCMD, node->args[0], 126);
	close(node->out);
}

void	command_get_redir(t_shell *shell, t_list *comnd)
{
	t_exec	*node;

	node = comnd->content;
	if (built_check(node))
		execute_builtin_command(shell, node, comnd);
	else
		execute_external_command(shell, comnd);
}

/*
void command_get_redir(t_shell *shell, t_list *comnd)
{
    t_exec *node;
    DIR *directory;
    char **str;
    pid_t pid;
    int status;
    int original_stdout;

    str = NULL;
    node = comnd->content;
    original_stdout = dup(STDOUT_FILENO); 

    if (built_check(node)) 
    {
        if (node->out != STDOUT_FILENO)
            dup2(node->out, STDOUT_FILENO);
        pipe_builtin(shell, comnd, &g_exit_status, ft_strlen(node->args[0]));
        dup2(original_stdout, STDOUT_FILENO);
        close(original_stdout);
        close(node->out);
        return;
    }
    directory = check_cmd(shell, comnd, &str);
    if (directory)
    {
        closedir(directory);
        m_error(ERR_ISDIR, node->args[0], 126);
        return;
    }
    if (node->path && access(node->path, X_OK) == 0)
    {
        pid = fork();
        if (pid < 0)
        {
            m_error(ERR_FORK, "Fork failed", 1);
            return;
        }
        else if (pid == 0)
        {
            if (node->out != STDOUT_FILENO)
                dup2(node->out, STDOUT_FILENO);
            
            directory = check_cmd(shell, comnd, &str);
            execve(node->path, node->args, shell->keys);
            exit(126);
        }
        else
        {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                g_exit_status = WEXITSTATUS(status);
            dup2(original_stdout, STDOUT_FILENO);
            close(original_stdout);
        }
    }
    else
        m_error(ERR_NEWCMD, node->args[0], 126);
    close(node->out);
}*/