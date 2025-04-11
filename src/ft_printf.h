/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:12:47 by dtheron           #+#    #+#             */
/*   Updated: 2024/11/29 14:53:47 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>

int	print(const char *p, int i, va_list args);
int	raccourcis(const char *p, int i, va_list args);
int	ft_printf(const char *str, ...);
int	ft_putnbr_base(unsigned long nbr, char *base);
int	ft_putadresse(void *r);
int	ft_putstr(char *str);
int	ft_putnbr(int nb);
int	ft_putnbr_unsigned(unsigned int nbd);
int	ft_putchar(char c);
int	count_numbers(int n);
int	ft_putnbr_base2(unsigned int nbr, char *base);

#endif