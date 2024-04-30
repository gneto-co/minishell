/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:51:33 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/29 10:54:27 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// i - int
// c - char
// s - char *
// a - char **
int	var_size(char op, int amount)
{
	int	nb;

	if (op == 'i')
		nb = sizeof(int);
	else if (op == 'c')
		nb = sizeof(char);
	else if (op == 's')
		nb = sizeof(char *);
	else if (op == 'a')
		nb = sizeof(char **);
	else
		nb = 0;
	return (nb * amount);
}
