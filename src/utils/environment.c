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

char	**dup_array(char **env)
{
	int		i;
	char	**sorted;

	i = 0;
	while (env[i])
		i++;
	sorted = malloc(sizeof(char *) * (i + 1));
	sorted[i] = NULL;
	i = -1;
	while (env[++i])
	{
		sorted[i] = ft_strdup(env[i]);
		if (sorted[i] == NULL)
		{
			while (i > 0)
				free(sorted[--i]);
			free(sorted);
			return (NULL);
		}
	}
	return (sorted);
}

void	sort_array(char **sorted)
{
	int		i;
	int		r;
	char	*tmp;

	tmp = NULL;
	r = 1;
	while (r)
	{
		i = -1;
		r = 0;
		while (sorted[++i])
		{
			if (sorted[i] && sorted[i + 1]
				&& ft_strncmp (sorted[i], sorted[i + 1],
					max_of(ft_strlen (sorted[i]),
						ft_strlen (sorted[i + 1]))) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[i + 1];
				sorted[i + 1] = tmp;
				r = 1;
			}
		}
	}
}

void	append_to_env(char *variable, char *value, int size, t_shell *shell)
{
	int		i;
	char	**updated_env;
	char	*new_env_var;
	char	*temp_str;

	i = 0;
	updated_env = malloc(sizeof(char *) * (size + 2));
	if (!updated_env)
		ft_error("malloc failed in append_to_env", 1);
	while (shell->keys[i])
	{
		updated_env[i] = ft_strdup(shell->keys[i]);
		i++;
	}
	temp_str = ft_strjoin(variable, "=");
	new_env_var = ft_strjoin(temp_str, value);
	free(temp_str);
	temp_str = NULL;
	updated_env[i++] = new_env_var;
	updated_env[i] = NULL;
	free_str_array(shell->keys);
	shell->keys = updated_env;
}
