/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:31:57 by emencova          #+#    #+#             */
/*   Updated: 2024/10/09 10:05:33 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <dirent.h>

void	initialize_pipeline_fds(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	redirect_input(int prev_fd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
}

void	redirect_output(int fd[2], t_list *cmd_node)
{
	if (cmd_node->next)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
	}
}

void	create_child_process(t_shell *shell, t_list *cmd_node, int prev_fd,
		int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		redirect_input(prev_fd);
		redirect_output(fd, cmd_node);
		close(fd[0]);
		command_get_pipeline(shell, cmd_node);
		exit(EXIT_SUCCESS);
	}
}

void	execute_pipeline(t_shell *shell, t_list *commands_list)
{
	int		fd[2];
	int		prev_fd;
	t_list	*cmd_node;

	prev_fd = -1;
	cmd_node = commands_list;
	while (cmd_node)
	{
		if (cmd_node->next)
			initialize_pipeline_fds(fd);
		create_child_process(shell, cmd_node, prev_fd, fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd_node->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmd_node = cmd_node->next;
	}
	while (wait(NULL) > 0)
	{
	}
}
