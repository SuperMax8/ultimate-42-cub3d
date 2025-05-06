/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:29:45 by dtheron           #+#    #+#             */
/*   Updated: 2025/05/06 16:10:25 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	count_negative;

	i = 0;
	result = 0;
	count_negative = 0;
	while (str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			count_negative = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (count_negative == 1)
		result = -result;
	return (result);
}

void	resizemap(t_map *map, t_cub *cub)
{
	int	i;
	int	d;

	d = 0;
	i = 0;
	(void)cub;
	while (map->map[d])
	{
		i = 0;
		while (map->map[d][i])
		{
			if (map->map[d][i] != 32 || map->map[d][i] != '\n')
			{
				map->map = map->map + d;
				return ;
			}
			i++;
		}
		d++;
	}
	return ;
}

char	*ft_strdups(char *str)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = malloc((sizeof(char) * ft_strlen(str)) + 1);
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_doublestrlen(char **str)
{
	int	d;

	d = 0;
	while (str[d])
		d++;
	return (d);
}
