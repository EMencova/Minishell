/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token_filler_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:48:35 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/09 09:48:45 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../exec/execute.h"

void	initialize_token(char **cmds, t_tokens **token, int i, int nbr)
{
	if (!valid_quotes(cmds[i]))
	{
		ft_error("Unclosed or unmatched quotes found", 1);
		return ;
	}
	(*token)[i].nbr = count_token(cmds[i]);
	(*token)[i].pipe = nbr;
	(*token)[i].tokens = token_split(cmds[i], (*token)[i].nbr);
	if (!(*token)[i].tokens)
	{
		ft_error("Token split failed\n", 1);
		return ;
	}
	(*token)[i].type = set_token((*token)[i]);
}

char	*expand_variable(char *original_token, int *k, t_shell *shell)
{
	char	*expanded_var;
	int		var_len;

	expanded_var = dollar_config(original_token, *k, shell);
	var_len = 1;
	if (ft_isalpha(original_token[*k + 1]) || original_token[*k + 1] == '_')
	{
		var_len++;
		while (ft_isalnum(original_token[*k + var_len]))
			var_len++;
	}
	*k += var_len;
	return (expanded_var);
}

char	*process_expansion(char *original_token, t_shell *shell)
{
	char	*expanded_str;
	char	*expanded_var;
	int		k;
	char	c[2];

	expanded_str = ft_strdup("");
	k = 0;
	while (original_token[k])
	{
		if (original_token[k] == '$')
		{
			expanded_var = expand_variable(original_token, &k, shell);
			expanded_str = ft_strjoin(expanded_str, expanded_var);
			free(expanded_var);
		}
		else
		{
			c[0] = original_token[k];
			c[1] = '\0';
			expanded_str = ft_strjoin(expanded_str, c);
			k++;
		}
	}
	return (expanded_str);
}
