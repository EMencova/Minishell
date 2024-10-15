/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:49:12 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/06 20:05:19 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_quote_state(char c, bool *in_quotes, char *quote_type)
{
	if ((c == '"' || c == '\'') && (*quote_type == '\0' || *quote_type == c))
	{
		if (!(*in_quotes))
		{
			*quote_type = c;
			*in_quotes = true;
		}
		else if (c == *quote_type)
		{
			*in_quotes = false;
			*quote_type = '\0';
		}
	}
}

bool	valid_quotes(const char *str)
{
	int		i;
	bool	in_quotes;
	char	quote_type;

	i = 0;
	in_quotes = false;
	quote_type = '\0';
	while (str[i])
	{
		handle_quote_state(str[i], &in_quotes, &quote_type);
		i++;
	}
	return (!in_quotes);
}
