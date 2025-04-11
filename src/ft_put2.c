/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:11:29 by dtheron           #+#    #+#             */
/*   Updated: 2024/11/28 19:11:30 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{
	char	d;
	int		count;
	int		nbd;

	nbd = nb;
	count = 0;
	if (nb == -2147483648)
	{
		count += write(1, "-2147483648", 11);
		return (count);
	}
	if (nb < 0)
	{
		count += write(1, "-", 1);
		nb = -nb;
	}
	if (nb / 10 != 0)
	{
		count += ft_putnbr(nb / 10);
	}
	d = nb % 10 + 48;
	count += write(1, &d, 1);
	return (count);
}

int	ft_putnbr_unsigned(unsigned int nbd)
{
	char			a;
	unsigned int	nb;
	int				count;

	count = 0;
	nb = nbd;
	if (nb < 10)
	{
		a = nb + '0';
		count += write(1, &a, 1);
	}
	if (nb >= 10)
	{
		count += ft_putnbr_unsigned(nb / 10);
		count += ft_putnbr_unsigned(nb % 10);
	}
	return (count);
}

int	ft_putchar(const char c)
{
	write(1, &c, 1);
	return (1);
}
