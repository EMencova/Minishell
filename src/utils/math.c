/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:51:43 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/06 20:15:51 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	absolute_value(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

int	count(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	max_of(int i, int j)
{
	if (i < j)
		return (j);
	else
		return (i);
}
