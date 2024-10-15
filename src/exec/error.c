/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:43:00 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 22:41:50 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <dirent.h>

void	m_error(int error_type, char *limit, int status)
{
	if (error_type == ERR_NEWDIR)
		ft_putstr_fd("no such file or directory: ", 2);
	else if (error_type == ERR_NOTDIR)
		ft_putstr_fd("not a directory: ", 2);
	else if (error_type == ERR_NWPERM)
		ft_putstr_fd("permission denied: ", 2);
	else if (error_type == ERR_DUP)
		ft_putstr_fd("dup2 error: ", 2);
	else if (error_type == ERR_FORK)
		ft_putstr_fd("fork error: ", 2);
	else if (error_type == ERR_QUOTE)
		ft_putstr_fd("error with matching quote\n", 2);
	else if (error_type == ERR_NEWCMD)
		ft_putstr_fd("command not found: ", 2);
	else if (error_type == ERR_PIPE)
		ft_putstr_fd("error creating pipe\n", 2);
	else if (error_type == ERR_PIPEND)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else if (error_type == ERR_MEM)
		ft_putstr_fd("no memory left on device\n", 2);
	else if (error_type == ERR_ISDIR)
		ft_putstr_fd("Is a directory: ", 2);
	ft_putstr_fd(limit, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = status;
}

int	error_unset(char *av)
{
	write(2, "bash: unset: '", 14);
	write(2, av, ft_strlen(av));
	write(2, "' : not a valid identifier\n", 27);
	return (1);
}

void	m_perror(const char *msg, const char *detail, int exit_code)
{
	if (exit_code == ERR_DUP)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	if (detail)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, detail, ft_strlen(detail));
	}
	write(STDERR_FILENO, "\n", 1);
	if (exit_code != 0)
		exit(exit_code);
}

void	free_exec_node(t_exec *exec_node)
{
	int	i;

	i = 0;
	if (exec_node)
	{
		if (exec_node->args)
		{
			while (exec_node->args[i])
			{
				free(exec_node->args[i]);
				i++;
			}
			free(exec_node->args);
		}
		free(exec_node->path);
		free(exec_node);
	}
}

void	ft_free(void *content)
{
	t_exec	*node;

	node = content;
	free_form(&node->args);
	free(node->path);
	if (node->in != STDIN_FILENO)
		close(node->in);
	if (node->out != STDOUT_FILENO)
		close(node->out);
	free(node);
}
