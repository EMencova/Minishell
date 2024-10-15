/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:13:24 by emencova          #+#    #+#             */
/*   Updated: 2023/10/08 15:26:20 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	size_t			i;

	a = (unsigned char *)s;
	i = 0;
	while (n > i)
	{
		if (a[i] == (unsigned char)c)
			return (&a[i]);
		i++;
	}
	return (0);
}
/*
int	main()
{
	const char str[] = "hello how are you";
	const char c = 'y';
	int		i;

	i = 20;

	printf("this is my function %p\n", ft_memchr(str, c, i));
	printf("this is official one %p", memchr(str, c, i));
	return (0);
}
*/
