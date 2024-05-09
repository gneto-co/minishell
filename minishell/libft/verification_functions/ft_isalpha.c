/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:05:32 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/08 10:07:18 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gets a char
// if is a letter of alphabet: return true
// else: return false
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1024);
	return (0);
}
