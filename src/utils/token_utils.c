/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:48:35 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/09 09:52:21 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../exec/execute.h"

int	count_token(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		i = skip_space(line, i);
		if (!line[i])
			break ;
		if (is_quote(line[i]))
		{
			i = handle_tquotes(line, i);
			if (i == -1)
				return (-1);
		}
		else
			i = handle_token(line, i);
		count++;
		if (line[i])
			i++;
	}
	return (count);
}

char	*extract_substring(char const *s, unsigned int start, size_t end)
{
	char	*sub;
	size_t	i;
	size_t	substring_len;

	substring_len = end - start;
	if (start >= end || substring_len == 0)
		return (NULL);
	sub = malloc(sizeof(char) * (substring_len + 1));
	if (sub == NULL)
		ft_error("malloc error in extract_substring", 1);
	i = 0;
	while (i < substring_len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
