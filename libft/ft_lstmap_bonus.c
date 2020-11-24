/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:58:32 by ygeslin           #+#    #+#             */
/*   Updated: 2019/10/20 18:49:48 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	if (!(lst2 = ft_lstnew(f(lst->content))))
		return (NULL);
	ptr = lst2;
	while (lst->next)
	{
		lst = lst->next;
		if (!(lst2->next = ft_lstnew(f(lst->content))))
			ft_lstclear(&ptr, del);
		lst2 = lst2->next;
	}
	return (ptr);
}
