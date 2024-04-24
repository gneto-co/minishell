/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 08:36:21 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:34:00 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*actual;
	t_list	*newlst;
	void	*newcontent;

	if (!lst)
		return (0);
	newlst = 0;
	while (lst)
	{
		newcontent = f(lst->content);
		actual = ft_lstnew(newcontent);
		if (!actual)
		{
			del(newcontent);
			ft_lstclear(&newlst, del);
			return (0);
		}
		ft_lstadd_back(&newlst, actual);
		lst = lst->next;
	}
	return (newlst);
}
