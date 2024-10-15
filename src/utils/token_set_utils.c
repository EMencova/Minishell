/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:48:35 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/08 10:19:51 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../exec/execute.h"

void	type_of_separator(int *type_of, char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i][0] != ' ' && token[i][0] != '\t')
			type_of[i] = -1;
		else
			type_of[i] = 1;
		i++;
	}
}

int	check_unclosed_quotes(char *str)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quote = !single_quote;
		else if (str[i] == '\"')
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

void	handle_quotes(char current_char, bool *in_quotes, char *quote_type)
{
	if ((current_char == '"' || current_char == '\'')
		&& (*quote_type == '\0' || *quote_type == current_char))
	{
		if (!*in_quotes)
		{
			*quote_type = current_char;
			*in_quotes = true;
		}
		else if (current_char == *quote_type)
		{
			*in_quotes = false;
			*quote_type = '\0';
		}
	}
}

bool	is_pipe(char current_char, bool in_quotes)
{
	return (current_char == '|' && !in_quotes);
}
