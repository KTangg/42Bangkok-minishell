/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 23:07:47 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/03 23:46:25 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*chk(t_list *new, void *(*f)(void *), void (*del)(void *), t_list *lst);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	newlist = chk(newlist, f, del, lst);
	temp = newlist;
	while (temp != NULL)
		temp = temp->next;
	return (newlist);
}

t_list	*chk(t_list *new, void *(*f)(void *), void (*del)(void *), t_list *lst)
{
	t_list	*curnew;

	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	curnew = new;
	lst = lst->next;
	while (lst != NULL)
	{
		curnew->next = ft_lstnew(f(lst->content));
		if (!curnew->next)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		curnew = curnew->next;
		lst = lst->next;
	}
	return (new);
}
