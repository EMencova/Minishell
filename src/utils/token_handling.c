/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:06:55 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/09 09:51:35 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

char	**token_split(char *line, int nbr)
{
	char	**token;
	int		i;

	i = -1;
	token = malloc(sizeof(char *) * (nbr + 1));
	if (!token)
		ft_error("malloc failed in token split", 1);
	token[nbr] = NULL;
	while (++i < nbr)
	{
		token[i] = parse_next_token(line, i, nbr);
	}
	return (token);
}

int	get_token_type(char *content, int len)
{
	if (ft_strncmp(">", content, max_of(1, len)) == 0)
		return (REDIR_OUT_SUBS);
	else if (ft_strncmp(">>", content, max_of(1, len)) == 0)
		return (REDIR_OUT_ATTACH);
	else if (ft_strncmp("<", content, max_of(1, len)) == 0)
		return (REDIR_IN);
	else if (ft_strncmp("<<", content, max_of(1, len)) == 0)
		return (HERE_DOC);
	return (0);
}

void	set_token_aux(int i, int *cmd, int *type)
{
	if (i && ((-REDIR_IN <= type[i - 1] && type[i - 1] <= -REDIR_OUT_SUBS)
			|| (REDIR_OUT_SUBS <= type[i - 1] && type[i - 1] <= REDIR_IN)))
		type[i] *= FILE;
	else if (i && (type[i - 1] == HERE_DOC || type[i - 1] == -HERE_DOC))
		type[i] *= HERE_DOC_END;
	else if (*cmd == 0)
	{
		*cmd = 1;
		type[i] *= CMD;
	}
	else
		type[i] *= ARG;
}

void	set_tokens_type(int *type, char **content)
{
	int	i;
	int	cmd;
	int	j;
	int	len;

	i = -1;
	cmd = 0;
	while (content[++i])
	{
		if (i == 0)
			j = 0;
		else
			j = 1;
		len = ft_strlen(content[i] + j);
		if (get_token_type(content[i] + j, len))
			type[i] = get_token_type(content[i] + j, len);
		else
			set_token_aux(i, &cmd, type);
	}
}

int	*set_token(t_tokens token)
{
	int	*type;

	type = malloc(sizeof(int) * (token.nbr + 1));
	if (type == NULL)
		ft_error("malloc failed in set token", 1);
	type_of_separator(type, token.tokens);
	set_tokens_type(type, token.tokens);
	return (type);
}
