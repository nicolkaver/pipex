/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:05:55 by nboratko          #+#    #+#             */
/*   Updated: 2021/12/12 17:15:16 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len(uintptr_t n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static void	ft_put_ptr(uintptr_t n, char *base)
{
	if (n / ft_strlen(base) > 0)
		ft_put_ptr((n / ft_strlen(base)), base);
	write(1, &base[n % ft_strlen(base)], 1);
}

int	ft_print_ptr(unsigned long long ptr)
{
	int					i;

	i = 0;
	if (!ptr)
	{
		write(1, "0x0", 3);
		return (3);
	}
	write(1, "0x", 2);
	i += 2;
	ft_put_ptr(ptr, HEX_LOW);
	i += len(ptr);
	return (i);
}
