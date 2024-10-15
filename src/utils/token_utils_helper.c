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

int	skip_space(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
			return (i);
	}
	return (i);
}

int	get_end(char *line, int i)
{
	if ((line[i] == '>' || line[i] == '<')
		&& count_backslash(line, i) % 2 == 0)
		i = token_redir_end(line, i);
	else if (line[i] == '$' && count_backslash(line, i) % 2 == 0)
		i = token_dollar_end(line, i);
	else if (line[i] == '\'' || line[i] == '\"')
	{
		i = token_quotes_end(line, i);
		if (i == -1)
			ft_error("syntax error, unclosed quotes.", 0);
	}
	else
		i = token_word_end(line, i);
	return (i);
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	handle_tquotes(char *line, int i)
{
	int	quote_end;

	quote_end = token_quotes_end(line, i);
	if (quote_end == -1)
		return (-1);
	return (quote_end + 1);
}

int	handle_token(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		return (i + 2);
	}
	while (line[i] && !isspace(line[i]) && line[i] != '>'
		&& line[i] != '<')
		i++;
	return (i);
}
