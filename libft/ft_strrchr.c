/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:36:05 by emencova          #+#    #+#             */
/*   Updated: 2023/10/08 15:27:55 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* to test before compiling
#include <stdio.h>
#include <string.h>

int	ft_strleng(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}
*/
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*a;

	a = (char *)s;
	i = ft_strlen(a);
	if (c == '\0')
		return (a + i);
	while (i != 0)
	{
		if (a[i] == (char)c)
			return (a + i);
		i--;
	}
	if (s[0] == (char)c)
		return (a);
	return (0);
}
/*
int	main()
{
	const char str[]= "hello hello how z are you";
	const char c = 'z';

	printf("my function- %s\n", ft_strrchr(str,c));

	printf("real function- %s", strrchr(str, c));

	return (0);
}*/
