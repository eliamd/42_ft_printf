/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:45:00 by edetoh            #+#    #+#             */
/*   Updated: 2024/10/28 12:57:07 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

static int	ft_putchar(char c)
{
	if (write(1, &c, 1))
		return (1);
	return (0);
}

static int	ft_putstr(char *s)
{
	int	str_len;

	str_len = ft_strlen(s);
	write(1, s, str_len);
	return (str_len);
}



static int	print_format(char format, va_list ap)
{
	int			count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(ap, int));
	if (format == 's')
		count += ft_putstr(va_arg(ap, char *));
	// if (format == 'p')
	// 	count += ft_putstr(va_arg(ap, char *));
	// if (format == 'i')
	// 	count += ft_putint(va_arg(ap, char *));
	// if (format == 'x')
	// 	count += ft_putint(va_arg(ap, char *));
	// if (format == 'X')
	// 	count += ft_putint(va_arg(ap, char *));
	// if (format == '%')
	// 	count += ft_putint(va_arg(ap, char *));
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

int	main(void)
{
	ft_printf("MOi ; Bonjour %s, merci %s!\n", "CCCCCCC", "AAA");
	printf("VRA ; Bonjour %s, merci %s!\n", "CCCCCCC", "AAA");
	return (1);
}
