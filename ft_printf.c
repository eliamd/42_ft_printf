/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:45:00 by edetoh            #+#    #+#             */
/*   Updated: 2024/10/28 17:38:43 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strdup(const char *s)
{
	char	*strduped;
	int		i;
	int		length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	strduped = malloc((length + 1) * sizeof(char));
	if (!strduped)
		return (NULL);
	i = 0;
	while (i < length)
	{
		strduped[i] = s[i];
		i++;
	}
	strduped[i] = '\0';
	return (strduped);
}

static int	ft_int_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		int_len;
	int		nb;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	int_len = ft_int_len(n);
	str = malloc((int_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	nb = n;
	str[int_len] = 0;
	if (n < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[--int_len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

static int	ft_unsigned_int_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	char				*str;
	int					int_len;
	unsigned int		nb;

	int_len = ft_unsigned_int_len(n);
	str = malloc((int_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	nb = n;
	str[int_len] = 0;
	if (n < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[--int_len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

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

int	ft_puthexlow(unsigned int num)
{
	char		*hex_digits;
	char		hex[8];
	int			i;
	int			count;

	hex_digits = "0123456789abcdef";
	i = 7;
	while (i >= 0)
	{
		hex[i] = hex_digits[num % 16];
		num /= 16;
		i--;
	}
	count = 0;
	i = 0;
	while (i < 8 && hex[i] == '0')
		i++;
	if (i == 8)
		i = 7;
	while (i < 8)
	{
		count += ft_putchar(hex[i]);
		i++;
	}
	return (count);
}

int	ft_puthexupp(unsigned int num)
{
	char		*hex_digits;
	char		hex[8];
	int			i;
	int			count;

	hex_digits = "0123456789ABCDEF";
	i = 7;
	while (i >= 0)
	{
		hex[i] = hex_digits[num % 16];
		num /= 16;
		i--;
	}
	count = 0;
	i = 0;
	while (i < 8 && hex[i] == '0')
		i++;
	if (i == 8)
		i = 7;
	while (i < 8)
	{
		count += ft_putchar(hex[i]);
		i++;
	}
	return (count);
}

static int	print_format(char format, va_list *ap)
{
	int			count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(*ap, int));
	else if (format == 's')
		count += ft_putstr(va_arg(*ap, char *));
	else if (format == 'p')
		count += ft_putadress(va_arg(*ap, char *));
	else if (format == 'd' || format == 'i')
		count += ft_putstr(ft_itoa(va_arg(*ap, int)));
	else if (format == 'u')
		count += ft_putstr(ft_unsigned_itoa(va_arg(*ap, unsigned int)));
	else if (format == 'x')
		count += ft_puthexlow(va_arg(*ap, unsigned int));
	else if (format == 'X')
		count += ft_puthexupp(va_arg(*ap, unsigned int));
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

int main(void)
{
	int resv;
	int resp;
	int *pointeur = &resv;

	resv = ft_printf("=== MON PRINTF ===\nchar : %c\nString : %s\nPointeur : %p\nDecimal : %d\nInteger : %i\nUnsigned decimal : %u\nHexadecimal (lowercase) : %x\nHexadecimal (uppercase) : %X\nPercent sign : %%\n",
					 'Z', "Bonjour", (void *)pointeur, 123, 21, 233323323, 166, 166);
	resp =    printf("=== VRA PRINTF ===\nchar : %c\nString : %s\nPointeur : %p\nDecimal : %d\nInteger : %i\nUnsigned decimal : %u\nHexadecimal (lowercase) : %x\nHexadecimal (uppercase) : %X\nPercent sign : %%\n",
					 'Z', "Bonjour", (void *)pointeur, 123, 21, 233323323, 166, 166);

	printf("=== Résultats ===\nMon printf a imprimé %d caractères\nVrai printf a imprimé %d caractères\n", resv, resp);

	return 0;
}
