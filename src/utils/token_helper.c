/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:11:10 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/07 22:15:51 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	token_dollar_end(char *str, int i)
{
	if (str[i + 1] && str[i + 1] == '$')
		return (1 + 2);
	i++;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\'' || str[i] == '\"' || str[i] == '>'
			|| str[i] == '<' || str[i] == '\0')
			return (i);
		else
			i++;
	}
	return (i);
}

int	token_word_end(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '$' || str[i] == ' ' || str[i] == '\t'
			|| str[i] == '>' || str[i] == '<' || str[i] == '\0')
			return (i);
		else if ((str[i] == '\'' || str[i] == '\"')
			&& (count_backslash(str, i) % 2 == 0))
			return (i);
		else
			i++;
	}
	return (i);
}

int	token_quotes_end(char *str, int i)
{
	int		j;
	char	quote_char;

	j = i + 1;
	quote_char = str[i];
	while (str[j])
	{
		if (str[j] == quote_char)
			return (j);
		j++;
	}
	ft_error("Error: unmatched quote\n", 1);
	return (-1);
}

int	token_redir_end(char *str, int i)
{
	int	j;

	j = i;
	while (str[i])
	{
		if (str[j] == str[i])
			i++;
		else
			return (i);
	}
	return (i);
}
