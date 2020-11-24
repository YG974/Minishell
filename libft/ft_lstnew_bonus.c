/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:56:35 by ygeslin           #+#    #+#             */
/*   Updated: 2019/10/17 20:53:27 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *lst;

	lst = NULL;
	if (!(lst = ft_calloc(sizeof(t_list), 1)))
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
