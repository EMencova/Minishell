/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:37:21 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 22:38:47 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	**allocate_and_copy(char **insd, int len, char *nstr)
{
	char	**out;
	int		i;

	i = -1;
	out = malloc(sizeof(char *) * (len + 2));
	if (!out)
		return (NULL);
	while (++i < len)
	{
		out[i] = ft_strdup(insd[i]);
		if (!out[i])
		{
			free_form(&out);
			return (NULL);
		}
	}
	out[i] = ft_strdup(nstr);
	if (!out[i])
	{
		free_form(&out);
		return (NULL);
	}
	out[i + 1] = NULL;
	return (out);
}

char	**extend_form(char **insd, char *nstr)
{
	int		len;
	char	**out;

	len = form_len(insd);
	if (!nstr || len < 0)
		return (insd);
	out = allocate_and_copy(insd, len, nstr);
	if (!out)
		return (insd);
	free_form(&insd);
	return (out);
}
