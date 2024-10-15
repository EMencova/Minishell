/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:09:53 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/06 20:14:52 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*set_dollar(char *str, int i, t_shell *shell)
{
	int		j;
	char	*tmp;

	j = i;
	while (str[++j])
	{
		if ((str[i] == ' ' || str[i] == '\t') && j == i + 1)
			return (ft_strdup("$"));
		else if ((str[i] == ' ' || str[i] == '\t'))
		{
			tmp = ft_substr(str, i, j - i);
			dollar_replace(&tmp, 0, shell);
			return (tmp);
		}
	}
	if (str[j - 1] == '$')
		return (ft_strdup("$"));
	tmp = ft_substr(str, i, j - i);
	dollar_replace(&tmp, 0, shell);
	return (tmp);
}

int	len_dollar(char *str, int i)
{
	int	j;

	j = i;
	while (str[++j])
	{
		if (str[j] == ' ' || str[j] == '\t')
			return (j - i);
	}
	return (j - i);
}
