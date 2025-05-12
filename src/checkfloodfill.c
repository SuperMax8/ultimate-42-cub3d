/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfloodfill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:29:33 by dtheron           #+#    #+#             */
/*   Updated: 2025/05/12 16:30:21 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	mapcopy(t_map *map)
{
	int	d;
	int	i;

	d = 0;
	i = 0;
	map->sizemap = ft_doublestrlen(map->map);
	map->mapcopy = malloc(sizeof(char *) * map->sizemap + 8);
	if (!map->mapcopy)
		return (0);
	while (map->map[d])
	{
		map->mapcopy[d] = ft_strdups(map->map[d]);
		if (!map->mapcopy)
			return (0);
		d++;
	}
	map->mapcopy[d] = NULL;
	return (1);
}

void	checkifvisited(t_map *map)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (map->mapcopy[d])
	{
		i = 0;
		while (map->mapcopy[d][i])
		{
			if (map->mapcopy[d][i] == 'V')
				map->mapcopy[d][i] = 'U';
			i++;
		}
		d++;
	}
}

int	floodfill(t_map *map, int i, int d)
{
	if (map->isgood)
		return (1);
	if (i < 0 || d < 0 || d >= map->sizemap || i >= ft_strlen(map->mapcopy[d]))
		return (0);
	if (!map->mapcopy[d])
		return (0);
	if (map->mapcopy[d][i] == 32 || map->mapcopy[d][i] == 'V')
		return (0);
	if (map->mapcopy[d][i] == 'U' || (map->x == i && map->y == d))
	{
		map->isgood = 1;
		return (1);
	}
	map->mapcopy[d][i] = 'V';
	floodfill(map, i + 1, d);
	floodfill(map, i - 1, d);
	floodfill(map, i, d + 1);
	floodfill(map, i, d - 1);
	if (map->isgood)
		return (1);
	return (0);
}
