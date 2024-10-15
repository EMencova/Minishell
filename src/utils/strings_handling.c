/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:31:24 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/06 20:16:39 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_stringjoin(char *str, char c)
{
	int		i;
	int		len;
	char	*new_string;

	i = 0;
	len = ft_strlen(str) + 1;
	if (c != '\0')
		len++;
	new_string = malloc(sizeof(char) * len);
	while (str[i])
	{
		new_string[i] = str[i];
		i++;
	}
	if (c != '\0')
		new_string[i++] = c;
	new_string[i] = '\0';
	free(str);
	return (new_string);
}
/*delete
char **separator_split(char *line, int *separatorI, int nbr_separator)
{
    int i;
    int j;
    char **content;

    content = malloc(sizeof(char *) * (nbr_separator + 2));
    if (!content)
        return NULL;
    i = 0;
    j = 0;
    while (i < nbr_separator + 1)
    {
        if (i == nbr_separator)
        {
            i = separatorI[nbr_separator - 1];
            if (j != 0)
                i = separatorI[nbr_separator - 1] + 1;
            content[i] = ft_substr(line, j, ft_strlen(line) - j);
            break ;
        }
        content[i] = ft_substr(line, j, separatorI[i] - j);
        if (content[i] == NULL)
            return (NULL);
        j = separatorI[i] + 1;
    }
    content[nbr_separator + 1] = NULL;
    return (content);
}*/

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!(str[i] && (str[i] == '-' || ('0' <= str[i] && str[i] <= '9'))))
		return (0);
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
