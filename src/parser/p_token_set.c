/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:47:09 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/08 18:01:40 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../exec/execute.h"

char	**lst_to_array(t_list *list)
{
	int		size;
	char	**array;
	int		i;

	size = ft_lstsize(list);
	array = malloc(sizeof(char *) * (size + 1));
	i = 0;
	if (!array)
		return (NULL);
	while (list)
	{
		array[i] = ft_strdup((char *)list->content);
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	*extract_command(char *line, int start, int end)
{
	char	*cmd;
	char	*clean_cmd;

	cmd = ft_substr(line, start, end - start);
	clean_cmd = remove_quotes(cmd);
	free(cmd);
	return (clean_cmd);
}

void	add_command_to_list(t_list **cmd_list, char *line, int start, int end)
{
	char	*cmd;

	cmd = extract_command(line, start, end);
	ft_lstadd_back(cmd_list, ft_lstnew(cmd));
}

t_list	*split_by_pipes(char *line)
{
	t_list	*cmd_list;
	int		i;
	int		start;
	bool	in_quotes;
	char	quote_type;

	cmd_list = NULL;
	i = 0;
	start = 0;
	in_quotes = false;
	quote_type = '\0';
	while (line[i])
	{
		handle_quotes(line[i], &in_quotes, &quote_type);
		if (is_pipe(line[i], in_quotes))
		{
			add_command_to_list(&cmd_list, line, start, i);
			start = i + 1;
		}
		i++;
	}
	if (start < i)
		add_command_to_list(&cmd_list, line, start, i);
	return (cmd_list);
}

char	**split_command_line(char *line)
{
	t_list	*cmd_list;
	char	**cmds;

	cmd_list = split_by_pipes(line);
	cmds = lst_to_array(cmd_list);
	ft_lstclear(&cmd_list, free);
	if (!cmds)
		ft_error("Failed to split commands by pipe\n", 1);
	return (cmds);
}
