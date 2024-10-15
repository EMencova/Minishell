/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:19:50 by emencova          #+#    #+#             */
/*   Updated: 2024/10/09 09:49:50 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../../minishell.h"

t_exec	*create_exec_node(char *cmd, t_tokens *token)
{
	t_exec	*exec_node;
	int		j;

	exec_node = malloc(sizeof(t_exec));
	j = 0;
	if (!exec_node)
		handle_memory_failure("Malloc failed for exec_node");
	exec_node->args = malloc(sizeof(char *) * (count_token(cmd) + 1));
	if (!exec_node->args)
		handle_memory_failure("Malloc failed for exec_node->args");
	while (token->tokens[j])
	{
		exec_node->args[j] = ft_strdup(token->tokens[j]);
		j++;
	}
	exec_node->args[j] = NULL;
	exec_node->path = NULL;
	exec_node->in = 0;
	exec_node->out = 1;
	return (exec_node);
}

void	add_exec_node_to_list(t_list **commands_list, t_exec *exec_node)
{
	t_list	*new_node;

	new_node = ft_lstnew(exec_node);
	if (!new_node)
		handle_memory_failure("Malloc failed for new_node");
	ft_lstadd_back(commands_list, new_node);
}

void	free_token_resources(t_tokens *token)
{
	free_tokens(token);
	free(token->type);
	free(token);
}

static void	process_command(char **cmd, int index,
		t_shell *shell, t_list **commands_list)
{
	t_tokens	*token;
	t_exec		*exec_node;

	token = create_and_fill_tokens(cmd, index, shell);
	if (!token)
	{
		ft_error("Error creating tokens", 1);
		return ;
	}
	exec_node = create_exec_node(*cmd, token);
	if (!exec_node || !(exec_node->args[0])
		|| ft_strlen(exec_node->args[0]) == 0
		|| ft_str_is_space(exec_node->args[0]))
	{
		free_token_resources(token);
		free(exec_node->args);
		free(exec_node);
		return ;
	}
	add_exec_node_to_list(commands_list, exec_node);
	free_token_resources(token);
}

void	tokenize_commands(char **cmdstr, t_list **commands_list, t_shell *shell)
{
	char	**cmds;
	int		i;

	cmds = split_command_line(*cmdstr);
	i = 0;
	if (!cmds)
	{
		handle_memory_failure("Error: split_command_line returned NULL\n");
		return ;
	}
	while (cmds[i])
	{
		process_command(&cmds[i], i, shell, commands_list);
		i++;
	}
	free_split(cmds);
}
