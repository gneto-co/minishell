/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:32:31 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:38:54 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// t_list *ft_lstdup(t_list *original_list)
// {
//     t_list  *new_list;

//     if (!original_list)
//         return (NULL);

//     new_list = ft_lstnew(original_list->content);
//     while (original_list)
//     {
//         original_list = original_list->next;
//         if (original_list)
//             ft_lstadd_back(new_list ,ft_lstnew(original_list->content));
//     }
//     return (new_list);
// }

// t_list *ft_lstdup(t_list *original_list)
// {
//     t_list  *new_list;
//     t_list  *first_node = NULL;

//     if (!original_list)
//         return (NULL);

//     new_list = ft_lstnew(original_list->content);
//     first_node = new_list;
//     while (original_list)
//     {
//         original_list = original_list->next;
//         if (original_list)
//         {
//             new_list = ft_lstnew(original_list->content);
//             ft_lstadd_back(&first_node, new_list);
//         }
//     }
//     return (first_node);
// }

t_list	*ft_lstdup(t_list *lst, void (*del)(void *),
		void *(*dupcontent)(void *))
{
	t_list	*actual;
	t_list	*newlst;
	void	*newcontent;

	if (!lst)
		return (0);
	newlst = 0;
	while (lst)
	{
		newcontent = dupcontent(lst->content);
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
