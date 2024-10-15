/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:41:25 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 20:45:05 by emencova         ###   ########.fr       */
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

static int	handle_builtin_command(t_shell *shell, t_exec *node, t_list *comnd)
{
	if (ft_strcmp(node->args[0], "env") == 0)
	{
		m_env(shell, node->args);
		return (1);
	}
	if (built_check(node))
	{
		pipe_builtin(shell, comnd, &g_exit_status, ft_strlen(node->args[0]));
		return (1);
	}
	return (0);
}

void	command_get_pipeline(t_shell *shell, t_list *comnd)
{
	t_exec	*node;
	DIR		*directory;
	char	**str;

	str = NULL;
	node = comnd->content;
	if (handle_builtin_command(shell, node, comnd))
		return ;
	directory = check_cmd(shell, comnd, &str);
	if (directory)
	{
		closedir(directory);
		m_error(ERR_ISDIR, node->args[0], 126);
		return ;
	}
	if (node->path && access(node->path, X_OK) == 0
		&& execve(node->path, node->args, shell->keys) == -1)
	{
		m_error(ERR_NEWCMD, node->args[0], 126);
		exit(126);
	}
	m_error(ERR_NEWCMD, node->args[0], 127);
	free_form(&str);
}

/*
void command_get_pipeline(t_shell *shell, t_list *comnd)
{
    t_exec *node;
    DIR *directory;
    char **str;

    str = NULL;
    node = comnd->content;
    if (handle_builtin_command(shell, node, comnd))
        return;
    directory = check_cmd(shell, comnd, &str);
    if (directory)
    {
        closedir(directory);
        m_error(ERR_ISDIR, node->args[0], 126);
        return;
    }
    if (node->path && access(node->path, X_OK) == 0)
    {
        if (execve(node->path, node->args, shell->keys) == -1)
        {
            m_error(ERR_NEWCMD, node->args[0], 126);
            exit(126);
        }
    }
    else
        m_error(ERR_NEWCMD, node->args[0], 127);
    free_form(&str);
}



void command_get_pipeline(t_shell *shell, t_list *comnd)
{
    t_exec *node;
    DIR *directory;
    char **str;

    str = NULL;
    node = comnd->content;
    if (ft_strcmp(node->args[0], "env") == 0)
    {
        m_env(shell, node->args);
        return;
    }
    if (built_check(node))
    {
        pipe_builtin(shell, comnd, &g_exit_status, ft_strlen(node->args[0]));
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
        if (execve(node->path, node->args, shell->keys) == -1)
        {
            m_error(ERR_NEWCMD, node->args[0], 126);
            exit(126);
        }
    }
    else
        m_error(ERR_NEWCMD, node->args[0], 127);
    free_form(&str);
}

*/