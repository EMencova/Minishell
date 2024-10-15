/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:27:18 by emencova          #+#    #+#             */
/*   Updated: 2023/10/07 12:11:09 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c <= '9' && c >= '0')
		|| (c <= 'z' && c >= 'a')
		|| (c <= 'Z' && c >= 'A'));
}
/*
#include <stdio.h>
#include <ctype.h>

int	main()
{
	char c;

	c = '5';
	printf("%d\n", ft_isalnum(c));
	printf("%d", isalnum(c));
	return (0);
}*/
