/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:55:41 by emencova          #+#    #+#             */
/*   Updated: 2023/10/07 13:17:55 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
*/

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	char	*strptr;
	size_t	i;

	strptr = (char *)ptr;
	i = 0;
	while (i < count)
	{
		strptr[i] = value;
		i++;
	}
	return (ptr);
}
/*
int	main()
{
	char str[40];

	strcpy(str,"You will see what will happen!");
        printf("%s\n", str);


	ft_memset(str, 'a', 20);
	printf("%s\n", str);

	memset(str,'a',20);
	printf("%s", str);
	return (0);
}
*/
