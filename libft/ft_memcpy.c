/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:06:51 by emencova          #+#    #+#             */
/*   Updated: 2023/10/07 14:41:45 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == 0 && src == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
/*
int	main()
{
	const char src[50] = "Hello how are you";
	char dest[50]= "this will change";
	printf("before memcpy = %s\n", dest);

	ft_memcpy(dest, src, 10);
	printf("after my function %s\n", dest);

	memcpy(dest, src, 10);
	printf("after normal function=  %s\n", dest);
	return(0);
}
*/
