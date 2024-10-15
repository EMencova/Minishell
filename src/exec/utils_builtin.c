/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:26:56 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 22:23:31 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_isspace(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	second_atoi(const char *str, long *n)
{
	int	sign;

	sign = 1;
	*n = 0;
	while (!ft_isspace(*str))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (-1);
	while (ft_isdigit(*str))
	{
		*n = 10 * (*n) + (*str - '0');
		str++;
	}
	if (*str && !ft_isspace(*str))
		return (-1);
	*n *= sign;
	return (0);
}

int	second_strchr(char *str, int c)
{
	unsigned char	c2;
	int				i;

	i = 0;
	if (!str)
		return (-1);
	c2 = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == c2)
			return (i);
		i++;
	}
	if (c2 == '\0')
		return (i);
	return (-1);
}

int	ft_charstr(const char *str, char *set)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (ft_strchr(set, str[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	put_form_fd(char **form, int newline, int fd)
{
	int	i;
	int	total_chars;

	total_chars = 0;
	i = 0;
	while (form && form[i])
	{
		if (newline)
			total_chars += ft_putendl_fd(form[i], fd);
		else
			total_chars += ft_putstr_fd(form[i], fd);
		i++;
	}
	return (total_chars);
}
