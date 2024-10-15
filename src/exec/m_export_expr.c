/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export_expr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:08:44 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 22:09:14 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*expand_value_if_needed(t_shell *shell, char *value)
{
	char	*expanded_value;

	if (value && value[0] == '$')
	{
		expanded_value = get_env_for_export(shell, value + 1);
		if (expanded_value)
		{
			free(value);
			value = ft_strdup(expanded_value);
			free(expanded_value);
		}
	}
	return (value);
}

void	add_or_update_env_var(t_shell *shell, char *var_name, char *value)
{
	int		index;
	char	*new_entry;
	char	*full_entry;

	index = find_key_idx(shell->keys, var_name);
	if (index != -1)
		set_env_ex(shell, var_name, value);
	else
	{
		new_entry = ft_strjoin(var_name, "=");
		full_entry = ft_strjoin(new_entry, value);
		free(new_entry);
		shell->keys = extend_form(shell->keys, full_entry);
		free(full_entry);
	}
}

void	handle_export_with_value(t_shell *shell, char *arg)
{
	char	*var_name;
	char	*value;

	split_var_value(arg, &var_name, &value);
	value = expand_value_if_needed(shell, value);
	if (var_name && is_valid_env_var(var_name))
		add_or_update_env_var(shell, var_name, value);
	else
		write(STDERR_FILENO, "Not a valid identifier\n", 23);
	free(var_name);
	free(value);
}

void	handle_export_without_value(t_shell *shell, char *arg)
{
	int	index;

	if (is_valid_env_var(arg))
	{
		index = find_key_idx(shell->keys, arg);
		if (index == -1)
			shell->keys = extend_form(shell->keys, ft_strjoin(arg, "="));
	}
	else
		write(STDERR_FILENO, "Not a valid identifier\n", 23);
}

int	m_export(t_shell *shell)
{
	int		i;
	char	**av;
	char	*equals_sign;

	av = ((t_exec *)shell->cmds->content)->args;
	i = 1;
	if (!av[1])
	{
		print_export(shell->keys);
		return (0);
	}
	while (av[i])
	{
		equals_sign = ft_strchr(av[i], '=');
		if (equals_sign)
			handle_export_with_value(shell, av[i]);
		else
			handle_export_without_value(shell, av[i]);
		i++;
	}
	return (1);
}
