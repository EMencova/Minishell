/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:37:19 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 20:41:16 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	cleanup_redirection_tokens(t_exec *node)
{
	int	i;

	i = 0;
	while (node->args[i])
	{
		if (ft_strcmp(node->args[i], "<") == 0
			|| ft_strcmp(node->args[i], ">") == 0
			|| ft_strcmp(node->args[i], ">>") == 0
			|| ft_strcmp(node->args[i], "<<") == 0)
		{
			node->args[i] = NULL;
		}
		i++;
	}
}

int	is_valid_env_var(const char *var_name)
{
	int	i;

	i = 0;
	while (ft_isspace(var_name[i]))
		i++;
	if (var_name[i] == '\0')
		return (0);
	while (var_name[i] != '\0')
		i++;
	while (ft_isspace(var_name[i - 1]))
		i--;
	return (i > 0);
}

int	is_invalid_var_assignment(char *cmd)
{
	char	*equals_sign;

	if (!cmd || !*cmd)
		return (0);
	equals_sign = ft_strchr(cmd, '=');
	if (equals_sign == cmd || (equals_sign != NULL
			&& *(equals_sign + 1) == '\0'))
		return (1);
	if (equals_sign != NULL && equals_sign == cmd + 1 && cmd[0] == ' ')
		return (1);
	return (0);
}
