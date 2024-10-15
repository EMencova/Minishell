/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:57:57 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/06 20:05:38 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_backslash(char *line, int i)
{
	int	count;

	count = 0;
	if (i == 0)
		return (0);
	while (i-- >= 0)
	{
		if (i >= 0 && line[i] == '\\')
			count++;
		else
			break ;
	}
	return (count);
}

void	join_backslash(char **path)
{
	int		i;
	char	*tmp;

	i = -1;
	if (path == NULL)
		return ;
	while (path [++i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = tmp;
	}
}
