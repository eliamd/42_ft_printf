/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:45:00 by edetoh            #+#    #+#             */
/*   Updated: 2024/10/28 14:22:39 by edetoh           ###   ########.fr       */
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

int	ft_putadress(void *ptr)
{
	uintptr_t		addr;
	char			*hex_digits;
	char			address[16];
	int				i;
	int				start;

	hex_digits = "0123456789abcdef";
	addr = (uintptr_t)ptr;
	i = 15;
	while (i >= 0)
	{
		address[i] = hex_digits[addr % 16];
		addr /= 16;
		i--;
	}
	write(1, "0x", 2);
	start = 0;
	while (start < 16 && address[start] == '0')
		start++;
	if (start == 16)
		start = 15;
	write(1, &address[start], 16 - start);
	return (2 + 16 - start);
}

static int	print_format(char format, va_list *ap)
{
	int			count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(*ap, int));
	if (format == 's')
		count += ft_putstr(va_arg(*ap, char *));
	if (format == 'p')
		count += ft_putadress(va_arg(*ap, char *));
	// if (format == 'i')
	// 	count += ft_putint(va_arg(ap, char *));
	// if (format == 'x')
	// 	count += ft_putint(va_arg(ap, char *));
	// if (format == 'X')
	// 	count += ft_putint(va_arg(ap, char *));
	// if (format == '%')
	// 	count += ft_putint(va_arg(ap, char *));
	else
		write(1, &format, 1);
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

int	main(void)
{
	int resp;
	int resv;

	int *pointeur = &resp;

	resv = ft_printf("=== MON PRINTF ===\nchar : %c\nString : %s\nPointeur : %p\n", 'Z', "Bonjour", (void *)pointeur);
	resp = printf("=== VRA PRINTF ===\nchar : %c\nString : %s\nPointeur : %p\n", 'Z', "Bonjour", (void *)pointeur);

	printf("\n%i = %i \n", resp, resv);
	return (1);
}
