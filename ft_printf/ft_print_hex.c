/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:45:16 by nboratko          #+#    #+#             */
/*   Updated: 2021/12/12 17:26:44 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len(unsigned int n)
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

static void	ft_put_hex(unsigned int n, char *base)
{
	if (n / ft_strlen(base) > 0)
		ft_put_hex((n / ft_strlen(base)), base);
	write(1, &base[n % ft_strlen(base)], 1);
}

int	ft_print_hex(unsigned int n, char *base)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_put_hex(n, base);
	i = len(n);
	return (i);
}
