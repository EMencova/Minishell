/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:34:30 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 21:09:37 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../../minishell.h"
#include <dirent.h>

void	cmd_execute(t_shell *shell, t_list *commands_list)
{
	t_exec	*exec;

	if (!commands_list)
	{
		write(STDERR_FILENO, "Error: No commands to execute\n", 31);
		return ;
	}
	exec = commands_list->content;
	if (is_invalid_var_assignment(exec->args[0]))
		return ;
	handle_redirection(shell, commands_list, exec);
}

void	handle_redirection(t_shell *shell, t_list *commands_list, t_exec *exec)
{
	int	check;

	check = parse_redir(exec, exec->args);
	if (check == 1)
		command_get_redir(shell, commands_list);
	else if (check == 5)
		command_get_redir_left(shell, commands_list);
	else if (check == 0)
		handle_execution(shell, commands_list, exec);
}

void	handle_execution(t_shell *shell, t_list *commands_list, t_exec *exec)
{
	if (exec->out == -1 || exec->in == -1)
		return ;
	if (commands_list->next)
		execute_pipeline(shell, commands_list);
	else
		command_get_single(shell, commands_list);
}
