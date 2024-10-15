/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:25:32 by emencova          #+#    #+#             */
/*   Updated: 2023/10/28 13:05:09 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* I had this only for testing before I compiled everything
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	ft_strlenght (char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*pt_src;

	pt_src = (char *)src;
	i = 0;
	while (i < size && *dst)
	{
		dst++;
		i++;
	}
	if (i == size)
		return (i + ft_strlen(src));
	j = 0;
	while (pt_src[j])
	{
		if (j < size - i - 1)
			*dst++ = pt_src[j];
		j++;
	}
	*dst = 0;
	return (j + i);
}
/*
int	main()
{
	char str[] = "hello hello";
	char dst[20]= "hello ";
	int		n;
	
	n = 20;
	ft_strlcat(dst, str, n);
	printf( "%s\n", dst);
	return (0);
}
*/
