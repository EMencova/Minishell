/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:24:25 by emencova          #+#    #+#             */
/*   Updated: 2023/10/08 12:43:35 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>
#include <ctype.h>
*/
int	ft_toupper(int c)
{
	if (c <= 'z' && c >= 'a')
	{
		c = c - 32;
	}
	return (c);
}
/*
int	main()
{
	int	c;

	c = 'z';
	printf("my function is %c\n", ft_toupper(c));

	printf("the real function is %c", toupper(c));
	return (0);
}*/
