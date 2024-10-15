/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_expr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:45:36 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 22:13:00 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	evaluate_expression(int num1, char op, int num2)
{
	if (op == '+')
		return (num1 + num2);
	else if (op == '-')
		return (num1 - num2);
	else if (op == '*')
		return (num1 * num2);
	else if (op == '/')
	{
		if (num2 == 0)
			return (-1);
		return (num1 / num2);
	}
	return (-1);
}

int	m_expr(char **args)
{
	int		num1;
	int		num2;
	char	op;
	int		result;

	if (!args[1] || !args[2] || !args[3])
		return (1);
	num1 = atoi(args[1]);
	op = args[2][0];
	num2 = atoi(args[3]);
	result = evaluate_expression(num1, op, num2);
	if (result == -1)
		return (1);
	printf("%d\n", result);
	return (0);
}
