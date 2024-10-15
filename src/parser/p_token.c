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

char	*parse_quoted_token(char *line, int *current_pos, int keep_quotes)
{
	char	quote_char;
	int		start;
	int		end;

	quote_char = line[(*current_pos)++];
	start = *current_pos;
	while (line[*current_pos] && line[*current_pos] != quote_char)
		(*current_pos)++;
	if (line[*current_pos] == quote_char)
	{
		end = *current_pos;
		(*current_pos)++;
		if (keep_quotes)
		{
			start--;
			end++;
		}
		return (extract_substring(line, start, end));
	}
	else
	{
		ft_error("Error: unmatched quote\n", 1);
		return (NULL);
	}
}

char	*parse_redirect_token(char *line, int *current_pos)
{
	int	start;
	int	end;

	start = (*current_pos)++;
	if (line[*current_pos] == line[start])
		(*current_pos)++;
	end = *current_pos;
	return (extract_substring(line, start, end));
}

char	*parse_simple_token(char *line, int *current_pos)
{
	int	start;
	int	end;

	start = *current_pos;
	while (line[*current_pos] && line[*current_pos] != ' '
		&& line[*current_pos] != '\t' && line[*current_pos] != '\"'
		&& line[*current_pos] != '\'' && line[*current_pos] != '>'
		&& line[*current_pos] != '<')
	{
		(*current_pos)++;
	}
	end = *current_pos;
	return (extract_substring(line, start, end));
}

char	*parse_next_token(char *line, int reset, int keep_quotes)
{
	static int	current_pos;

	if (reset == 0)
		current_pos = 0;
	current_pos = skip_space(line, current_pos);
	if (!line[current_pos])
		return (NULL);
	if (line[current_pos] == '\"' || line[current_pos] == '\'')
		return (parse_quoted_token(line, &current_pos, keep_quotes));
	else if (line[current_pos] == '>' || line[current_pos] == '<')
		return (parse_redirect_token(line, &current_pos));
	else
		return (parse_simple_token(line, &current_pos));
	return (NULL);
}
