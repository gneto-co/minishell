/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:43:52 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:36:50 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*actual;

	if (!*lst)
		return ;
	while (*lst)
	{
		actual = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = actual;
	}
	lst = NULL;
}
