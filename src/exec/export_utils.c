/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:40:19 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 21:49:30 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	sort_keys(char **keys)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (keys[i] != NULL)
	{
		j = i + 1;
		while (keys[j] != NULL)
		{
			if (ft_strcmp(keys[i], keys[j]) > 0)
			{
				temp = keys[i];
				keys[i] = keys[j];
				keys[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(char **keys)
{
	int	i;

	sort_keys(keys);
	i = 0;
	while (keys[i])
	{
		printf("declare -x %s\n", keys[i]);
		i++;
	}
}

char	*remove_quotes(char *token)
{
	int		len;
	char	*new_token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(token);
	new_token = malloc(len + 1);
	if ((token[0] == '\'' || token[0] == '"') && (token[len - 1] == token[0]))
	{
		i++;
		len--;
	}
	while (i < len)
		new_token[j++] = token[i++];
	new_token[j] = '\0';
	return (new_token);
}

void	remove_quotes_ifneeded(char **value)
{
	size_t	len;

	len = ft_strlen(*value);
	if (len >= 2 && ((*value)[0] == '"' && (*value)[len - 1] == '"'))
	{
		(*value)[len - 1] = '\0';
		ft_memmove(*value, *value + 1, len - 1);
	}
	else if (len >= 2 && ((*value)[0] == '\'' && (*value)[len - 1] == '\''))
	{
		(*value)[len - 1] = '\0';
		ft_memmove(*value, *value + 1, len - 1);
	}
}

void	split_var_value(char *arg, char **var, char **value)
{
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
	{
		*var = NULL;
		*value = NULL;
		return ;
	}
	*var = ft_strndup(arg, eq_pos - arg);
	if (*(eq_pos + 1) != '\0')
	{
		*value = ft_strdup(eq_pos + 1);
		remove_quotes_ifneeded(value);
	}
	else
		*value = ft_strdup("");
}
