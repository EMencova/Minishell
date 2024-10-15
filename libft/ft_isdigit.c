/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:24:07 by emencova          #+#    #+#             */
/*   Updated: 2023/10/11 11:20:38 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}
/*
#include <stdio.h>
#include <ctype.h>

int main ()
{
	char c;

	c = '+';
	printf("%d\n", ft_isdigit(c));
	printf("%d", isdigit(c));
	return (0);
}*/
