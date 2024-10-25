/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:45:00 by edetoh            #+#    #+#             */
/*   Updated: 2024/10/25 18:16:11 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static

static int	print_format(char format, va_list ap)
{
	int			count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(ap, char)); // A FAIRE
	if (format == 's')
		count += ft_putstr(va_arg(ap, char *)); // A FAIRE
	if (format == 'p')
		count += ft_putstr(va_arg(ap, char *)); // A FAIRE
	if (format == 'i')
		count += ft_putint(va_arg(ap, char *));
	if (format == 'x')
		count += ft_putint(va_arg(ap, char *));
	if (format == 'X')
		count += ft_putint(va_arg(ap, char *));
	if (format == '%')
		count += ft_putint(va_arg(ap, char *));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			count;

	count = 0;
	va_start(ap, str);
	while (*str != '\0')
	{
		if (*str == '%')
			count += print_format(*(++str), ap);
		else
			count += write(1, str, 1);
		str++;
	}
	va_end(ap);
	return (count);
}
