/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:47:07 by nboratko          #+#    #+#             */
/*   Updated: 2021/12/12 17:12:48 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_nbr(long int n)
{
	int		i;
	char	*s;

	i = 0;
	ft_putnbr(n);
	s = ft_itoa(n);
	i = ft_strlen(s);
	free(s);
	return (i);
}

int	ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	ft_putstr(str);
	i = ft_strlen(str);
	return (i);
}

int	ft_print_pct(void)
{
	write(1, "%", 1);
	return (1);
}
