/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:50:14 by yfontene          #+#    #+#             */
/*   Updated: 2024/10/08 10:41:07 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../exec/execute.h"

char	**duplicate_and_sort_keys(char **keys)
{
	char	**sorted_keys;

	sorted_keys = dup_array(keys);
	if (!sorted_keys)
		return (NULL);
	sort_array(sorted_keys);
	return (sorted_keys);
}

void	populate_keys(char **env, t_shell *shell)
{
	int	i;

	i = 0;
	shell->keys[i] = ft_strdup("?=0");
	while (env[i])
	{
		shell->keys[i + 1] = ft_strdup(env[i]);
		if (!shell->keys[i + 1])
			ft_error("malloc failed", 1);
		i++;
	}
	shell->keys[i + 1] = NULL;
}

char	**allocate_keys(int env_size)
{
	char	**keys;

	keys = malloc(sizeof(char *) * (env_size + 2));
	if (!keys)
		ft_error("malloc failed", 1);
	return (keys);
}

int	get_env_size(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

void	env_init(char **env, t_shell *shell)
{
	int		env_size;
	char	**sorted_env;

	env_size = get_env_size(env);
	shell->keys = allocate_keys(env_size);
	populate_keys (env, shell);
	sorted_env = duplicate_and_sort_keys(shell->keys);
	if (!sorted_env)
	{
		free_form(&shell->keys);
		ft_error("malloc failed", 1);
	}
	free_str_array(sorted_env);
}
