/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:44:34 by emencova          #+#    #+#             */
/*   Updated: 2023/10/08 12:49:29 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <ctype.h>
#include <stdio.h>
*/
int	ft_tolower(int c)
{
	if (c <= 'Z' && c >= 'A')
	{
		c = c + 32;
	}
	return (c);
}
/*
int	main()
{
	int	c;

	c = 'U';
	printf("my function is %c\n", ft_tolower(c));
	printf("the real function is %c", tolower(c));
	return (0);
}
*/
