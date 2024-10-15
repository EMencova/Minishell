/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:46:27 by emencova          #+#    #+#             */
/*   Updated: 2023/10/09 12:11:42 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>
#include <string.h>
int	ft_stlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}
int	ft_strcmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && n--)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;
	char	*l;

	l = ((char *)little);
	if (*little == 0)
		return ((char *)big);
	n = ft_strlen(l);
	while (*big && n <= len)
	{
		if (*big == *little && ft_strncmp(big, little, n) == 0)
			return ((char *)big);
		++big;
		--len;
	}
	return (0);
}
/*
int	main()
{
	const char big[] = "how hello";
	const char little[]= "hello";
	size_t	n;

	n = 20;
	printf("my function %s\n", ft_strnstr(big, little, n));
//	printf("official function %s", strnstr(big, little, n));
	return (0);
}
*/
