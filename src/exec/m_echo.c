/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:15:09 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 22:01:33 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_no_newline_option(char *arg)
{
	if (!ft_strncmp(arg, "-n", 2)
		&& char_count(arg, 'n') == (int)(ft_strlen(arg) - 1))
		return (1);
	return (0);
}

void	print_echo_args(char **args, int start_idx, int add_space)
{
	int	i;

	i = start_idx;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (add_space)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	m_echo(char **args)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	if (!args || !args[0])
		return (0);
	while (args[i] && is_no_newline_option(args[i]))
	{
		new_line = 0;
		i++;
	}
	print_echo_args(args, i, new_line);
	return (0);
}
