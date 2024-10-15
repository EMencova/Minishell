/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token_filler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:48:35 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/09 09:48:54 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../exec/execute.h"

void	process_token(t_tokens *token, int i, int j, t_shell *shell)
{
	char	*original_token;
	char	*expanded_str;

	if (token[i].tokens[j][0] == '\"'
			&& token[i].tokens[j][ft_strlen(token[i].tokens[j]) - 1] == '\"')
	{
		original_token = remove_quotes(token[i].tokens[j]);
		expanded_str = process_expansion(original_token, shell);
		free(token[i].tokens[j]);
		free(original_token);
		token[i].tokens[j] = expanded_str;
	}
	else if (token[i].tokens[j][0] == '\''
			&& token[i].tokens[j][ft_strlen(token[i].tokens[j]) - 1] == '\'')
		token[i].tokens[j] = remove_quotes(token[i].tokens[j]);
	else if (token[i].tokens[j][0] == '$')
	{
		if (ft_isalpha(token[i].tokens[j][1]) || token[i].tokens[j][1] == '_'
				|| token[i].tokens[j][1] == '?')
			token[i].tokens[j] = dollar_config(token[i].tokens[j], 0, shell);
		else
			token[i].tokens[j] = ft_strdup(token[i].tokens[j]);
	}
}

void	combine_tokens(t_tokens *token, int i, int j)
{
	char	*temp;

	if (j > 1 && ft_strchr(token[i].tokens[j - 2], '='))
	{
		temp = ft_strjoin(token[i].tokens[j - 2], token[i].tokens[j - 1]);
		free(token[i].tokens[j - 2]);
		free(token[i].tokens[j - 1]);
		token[i].tokens[j - 2] = temp;
		token[i].tokens[j - 1] = NULL;
	}
	token[i].tokens[j] = NULL;
}

void	filler_stokens(char **cmds, t_tokens **token, int nbr, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	initialize_token(cmds, token, i, nbr);
	while ((*token)[i].tokens[j])
	{
		process_token(*token, i, j, shell);
		j++;
	}
	combine_tokens(*token, i, j);
}
