/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:15:46 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/06 20:20:12 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

/*int is_protected(int type)
{
	if (type == PROTECTED_DOLLAR || type == -PROTECTED_DOLLAR)
		return (1);
	if (type == PROTECTED_QUOTE || type == -PROTECTED_QUOTE)
		return (1);
	return (0);
}

int is_cmd(int type)
{
    if (type == CMD || type == -CMD)
        return (1);
    return (0);
}

int is_arg(int type)
{
    if (type == ARG || type == -ARG)
        return (1);
    return (0);
}

int is_redirection(int type)
{
    if (type == REDIR_IN || type == -REDIR_IN)
        return (1);
    if (type == REDIR_OUT_SUBS || type == -REDIR_OUT_SUBS)
        return (1);
    if (type == REDIR_OUT_ATTACH || type == -REDIR_OUT_ATTACH)
        return (1);
    if (type == HERE_DOC || type == -HERE_DOC)
        return (1);
    if (type == REDIR_DOC || type == -REDIR_DOC)
        return (1);
    return (0);
}*/
