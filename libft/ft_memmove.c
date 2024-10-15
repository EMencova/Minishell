/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:42:43 by emencova          #+#    #+#             */
/*   Updated: 2023/10/07 15:01:02 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	if ((size_t)dst - (size_t)src < len)
	{
		i = len -1;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}
/*
int	main()
{
	char dest[] = "lets see what will happen";
	const char src[] = "you see now";

	printf("before test\n\n dest=  %s\n src= %s\n\n", dest, src);

	ft_memmove(dest, src, 8);
	printf( "after test\n\n dest= %s\n src= %s\n\n", dest, src);

	memmove(dest, src, 8);
	printf(" test with normal function\n\n dest= %s\n src= %s\n", dest, src);
	return (0);
}*/
