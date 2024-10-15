/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:46:07 by emencova          #+#    #+#             */
/*   Updated: 2024/10/07 19:54:17 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*ft_strdup(const char *src)
{
	char	*dest;
	char	*s;
	size_t	i;

	s = ((char *)src);
	i = ft_strlen(s) + 1;
	dest = (char *)malloc(sizeof(*src) * i);
	if (!dest)
		return (0);
	return ((char *)ft_memcpy(dest, s, i));
}*/

char	*ft_strdup(const char *s1)
{
	char	*result;

	result = (char *)malloc(ft_strlen(s1) + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, ft_strlen(s1) + 1);
	return (result);
}
/*int	main()
{
	char	str[] = "Hello";
	char	str1[] = "I hope you have a good day";
	char	str2[] = "Every day!";
	ft_putendl_fd(ft_strdup(str), 1);
	ft_putendl_fd(ft_strdup(str1), 1);
	ft_putendl_fd(ft_strdup(str2), 1);
}*/
