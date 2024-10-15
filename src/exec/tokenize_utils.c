/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:18:07 by emencova          #+#    #+#             */
/*   Updated: 2024/10/09 09:49:59 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../../minishell.h"

void	duplicate_file_descriptors(int *original_stdout, int *original_stdin)
{
	*original_stdout = dup(STDOUT_FILENO);
	*original_stdin = dup(STDIN_FILENO);
}

void	restore_file_descriptors(int original_stdout, int original_stdin)
{
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
}

void	handle_memory_failure(char *message)
{
	ft_error(message, 1);
}

t_tokens	*create_and_fill_tokens(char **cmd, int index, t_shell *shell)
{
	t_tokens	*token;

	token = malloc(sizeof(t_tokens));
	if (!token)
		handle_memory_failure("Malloc failed in tokenize_commands\n");
	filler_stokens(cmd, &token, index, shell);
	return (token);
}

void	remove_quotes_from_args(t_exec *node)
{
	int		i;
	char	*temp;

	i = 0;
	while (node->args[i])
	{
		temp = remove_quotes(node->args[i]);
		if (temp)
		{
			free(node->args[i]);
			node->args[i] = temp;
		}
		i++;
	}
}
