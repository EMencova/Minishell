/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:13:38 by emencova          #+#    #+#             */
/*   Updated: 2023/10/28 12:59:16 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_reset(t_list *lst, void *content, void (*del)(void *))
{
	if (del && content)
		del(content);
	ft_lstclear(&lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*temp;
	void	*content;

	list = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (ft_reset(list, content, del));
		temp = ft_lstnew(content);
		if (!temp)
			return (ft_reset(list, content, del));
		ft_lstadd_back(&list, temp);
		lst = lst -> next;
	}
	return (list);
}
