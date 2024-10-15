/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:14:59 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/07 22:45:22 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../exec/execute.h"

void	free_tokens(t_tokens *token)
{
	int	i;

	i = 0;
	if (!token || !token->tokens)
		return ;
	while (token->tokens[i])
	{
		free(token->tokens[i]);
		token->tokens[i] = NULL;
		i++;
	}
	free(token->tokens);
	token->tokens = NULL;
}

void	free_dollar(char **original, char **replacement)
{
	int	i;

	i = -1;
	while (original[++i])
	{
		free(original[i]);
		original[i] = NULL;
	}
	i = -1;
	while (replacement[++i])
	{
		free(replacement[i]);
		replacement[i] = NULL;
	}
	free(original);
	free(replacement);
	original = NULL;
	replacement = NULL;
}

void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
