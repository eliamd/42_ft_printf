/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:01:43 by edetoh            #+#    #+#             */
/*   Updated: 2024/10/28 18:01:54 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
