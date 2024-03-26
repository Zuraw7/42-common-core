/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:52:47 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/04 17:52:47 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;

	newlst = NULL;
	while (lst != NULL)
	{
		newnode = ft_lstnew(f(lst->content));
		if (newnode == NULL)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		if (newlst == NULL)
			newlst = newnode;
		else
			ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return (newlst);
}
