/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_power_of.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:46:05 by gneto-co          #+#    #+#             */
/*   Updated: 2023/12/29 20:54:24 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	op_square(int number)
{
	return (number * number);
}

int	op_power_of(int base, int exponent)
{
	int	number;

	number = 1;
	while (exponent--)
		number *= base;
	return (number);
}
