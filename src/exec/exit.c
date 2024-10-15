/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:15:25 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 21:40:06 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	parse_sign(const char **str, int *sign)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign = -1;
		*str += 1;
	}
}

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	parse_sign(&str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LLONG_MAX - (*str - '0')) / 10)
		{
			if (sign == 1)
				return (LLONG_MAX);
			return (LLONG_MIN);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	validate_exit_arguments(t_exec *cmd, int *leave)
{
	char	*arg;
	int		i;

	if (!cmd->args || !cmd->args[1])
		exit(0);
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		*leave = 0;
		return (1);
	}
	arg = cmd->args[1];
	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]) && !(i == 0 && (arg[i] == '-' \
			|| arg[i] == '+')))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit(1);
		}
		i++;
	}
	return (0);
}

int	m_exit(t_shell *shell, t_list *cmd_node, int *leave)
{
	t_exec			*cmd;
	long long int	long_exit_value;
	int				exit_value;

	cmd = (t_exec *)cmd_node->content;
	*leave = !shell->cmds->next;
	if (validate_exit_arguments(cmd, leave))
		return (1);
	long_exit_value = ft_atoll(cmd->args[1]);
	if (long_exit_value < INT_MIN || long_exit_value > INT_MAX)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		return (1);
	}
	exit_value = (int)(long_exit_value % 256);
	if (exit_value < 0)
		exit_value += 256;
	exit(exit_value);
}
