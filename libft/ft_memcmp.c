/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:30:12 by emencova          #+#    #+#             */
/*   Updated: 2023/10/14 10:34:06 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) -
					*(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}
/*
int	main ()
{
	const char src[50] = "hey";
	char src2[50] = "hello";
	int	n;

	n = 30;
	printf("my function is %d\n", ft_memcmp(src, src2 , n));
	printf("official function is %d", memcmp(src, src2, n));
	return (0);
}
*/
