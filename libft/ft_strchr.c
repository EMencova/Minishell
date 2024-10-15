/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:08:20 by emencova          #+#    #+#             */
/*   Updated: 2023/10/14 10:40:54 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <string.h>
*/
char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}
/*
int	main()
{
	const char	*str;
	int	c;

	str = "hello. a annalisa an";
	c = '.';
	printf("my function %s\n", ft_strchr(str, c));

	printf("real function %s", strchr(str, c));

	return (0);
}
*/
