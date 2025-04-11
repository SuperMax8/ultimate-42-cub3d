/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:26:01 by dtheron           #+#    #+#             */
/*   Updated: 2024/11/28 19:22:13 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base2(unsigned int nbr, char *base)
{
	unsigned int	nb;
	int				s;

	s = 0;
	nb = nbr;
	if (nb >= 16)
		s += ft_putnbr_base(nb / 16, base);
	nb = nb % 16;
	s += write(1, &base[nb], 1);
	return (s);
}

int	ft_putnbr_base(unsigned long nbr, char *base)
{
	unsigned long	nb;
	int				s;

	s = 0;
	nb = nbr;
	if (nb >= 16)
		s += ft_putnbr_base(nb / 16, base);
	nb = nb % 16;
	s += write(1, &base[nb], 1);
	return (s);
}

int	ft_putadresse(void *r)
{
	int				count;
	unsigned long	adresse;

	count = 0;
	adresse = (unsigned long)r;
	if (adresse == 0)
	{
		count += write(1, "(nil)", 5);
		return (count);
	}
	write(1, "0", 1);
	write(1, "x", 1);
	count += 2;
	count += ft_putnbr_base(adresse, "0123456789abcdef");
	return (count);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		i += write(1, "(null)", 6);
		return (i);
	}
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}
