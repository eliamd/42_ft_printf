/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:45:00 by edetoh            #+#    #+#             */
/*   Updated: 2024/11/01 14:08:33 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	print_format(char format, va_list *ap)
{
	int			count;

	count = 0;
	if (format == 'c')
		count += ft_putchar_fd(va_arg(*ap, int), 1);
	else if (format == 's')
		count += ft_putstr_fd(va_arg(*ap, char *), 1);
	else if (format == 'p')
		count += ft_putadress(va_arg(*ap, char *));
	else if (format == 'd' || format == 'i')
		count += ft_putstr_fd(ft_itoa(va_arg(*ap, int)), 1);
	else if (format == 'u')
		count += ft_putstr_fd(ft_unsigned_itoa(va_arg(*ap, unsigned int)), 1);
	else if (format == 'x')
		count += ft_puthexlow(va_arg(*ap, unsigned int));
	else if (format == 'X')
		count += ft_puthexup(va_arg(*ap, unsigned int));
	else
	{
		write(1, &format, 1);
		count++;
	}
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
		{
			str++;
			if (*str != '\0')
			{
				count += print_format(*str, &ap);
			}
		}
		else
			count += write(1, str, 1);
		str++;
	}
	va_end(ap);
	return (count);
}
