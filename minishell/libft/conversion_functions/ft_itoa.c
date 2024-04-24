/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:43:27 by gneto-co          #+#    #+#             */
/*   Updated: 2023/11/15 10:17:25 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	size_of_int(int long nbr)
{
	int	i;

	i = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static void	size_to_cases(int *nblen)
{
	int	nb_cases;

	nb_cases = 1;
	while (--(*nblen))
		nb_cases *= 10;
	*nblen = nb_cases;
}

static void	negative_stuff(int long *nbr, int *sinal)
{
	*sinal = 0;
	if (*nbr < 0)
		*sinal = 1;
	if (*sinal)
		*nbr *= -1;
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			sinal;
	int			nblen;
	int long	nbr;

	i = 0;
	nbr = n;
	negative_stuff(&nbr, &sinal);
	nblen = size_of_int(nbr);
	str = malloc(sizeof(char) * (nblen + 1 + sinal));
	if (!str)
		return (NULL);
	if (sinal)
		str[i++] = '-';
	size_to_cases(&nblen);
	while (nblen >= 10)
	{
		str[i++] = '0' + (nbr / nblen);
		nbr %= nblen;
		nblen /= 10;
	}
	str[i] = '0' + (nbr % 10);
	str[++i] = '\0';
	return (str);
}
