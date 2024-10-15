/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:01:48 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 15:41:09 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./src/exec/execute.h"

void	process_command_line(char *line, t_shell *shell)
{
	t_list	*command_list;

	command_list = NULL;
	add_history(line);
	tokenize_commands(&line, &command_list, shell);
	shell->cmds = command_list;
	if (command_list)
		cmd_execute(shell, command_list);
	ft_lstclear(&command_list, ft_free);
	shell->cmds = NULL;
}

void	cleanup_shell(t_shell *shell)
{
	int	i;

	if (shell->cmds)
	{
		ft_lstclear(&(shell->cmds), ft_free);
		shell->cmds = NULL;
	}
	if (shell->keys)
	{
		i = 0;
		while (shell->keys[i])
		{
			free(shell->keys[i]);
			i++;
		}
		free(shell->keys);
		shell->keys = NULL;
	}
}
