/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:48:49 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/06 19:49:51 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_env_value(char *str, int i, char **sorted)
{
	int		j;
	int		name_len;
	char	*env_value;

	j = 0;
	env_value = NULL;
	if (str[i] == '$')
		i++;
	name_len = 0;
	while (str[i + name_len] && (ft_isalnum(str[i + name_len])
			|| str[i + name_len] == '_'))
		name_len++;
	while (sorted[j])
	{
		if (ft_strncmp(str + i, sorted[j], name_len) == 0
			&& sorted[j][name_len] == '=')
		{
			env_value = ft_strdup(ft_strchr(sorted[j], '=') + 1);
			return (env_value);
		}
		j++;
	}
	return (ft_strdup(""));
}
