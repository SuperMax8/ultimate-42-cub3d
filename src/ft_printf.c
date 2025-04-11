/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:25:47 by dtheron           #+#    #+#             */
/*   Updated: 2024/12/03 16:20:51 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <fcntl.h>

int	print(const char *p, int i, va_list args)
{
	int	count;

	count = 0;
	if (p[i] == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (p[i] == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (p[i] == 'p')
		count += ft_putadresse(va_arg(args, void *));
	else if (p[i] == 'd')
		count += ft_putnbr(va_arg(args, int));
	else if (p[i] == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (p[i] == 'u')
		count += ft_putnbr_unsigned(va_arg(args, unsigned long));
	else if (p[i] == 'x')
		count += ft_putnbr_base2(va_arg(args, unsigned int),
				"0123456789abcdef");
	else if (p[i] == 'X')
		count += ft_putnbr_base2(va_arg(args, unsigned int),
				"0123456789ABCDEF");
	else if (p[i] == '%')
		count += write(1, "%", 1);
	return (count);
}

int	raccourcis(const char *p, int i, va_list args)
{
	int	count;
	int	ret;

	count = 0;
	ret = 0;
	while (p[i] != '\0')
	{
		if (p[i] == '%' && (p[i + 1] == 's' || p[i + 1] == 'c' || p[i
					+ 1] == 'p' || p[i + 1] == 'd' || p[i + 1] == 'i' || p[i
					+ 1] == 'u' || p[i + 1] == 'x' || p[i + 1] == 'X' || p[i
					+ 1] == '%'))
		{
			i++;
			ret = print(p, i, args);
		}
		else
			ret = write(1, &p[i], 1);
		if (ret == -1)
			return (-1);
		count += ret;
		i++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	const char	*p;
	int			i;
	int			count;
	va_list		args;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	p = str;
	count = 0;
	count += raccourcis(p, i, args);
	va_end(args);
	return (count);
}
