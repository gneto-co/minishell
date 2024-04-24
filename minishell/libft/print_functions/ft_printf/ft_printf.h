/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:55:49 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/14 00:32:43 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../libft.h"
# include <stdarg.h>

int		ft_printf(const char *str, ...);
size_t	print_di(va_list args);
size_t	print_u(va_list args);
size_t	print_o(va_list args);
size_t	print_x(va_list args);
size_t	print_xx(va_list args);
size_t	print_c(va_list args);
size_t	print_s(va_list args);
size_t	print_p(va_list args);

#endif
