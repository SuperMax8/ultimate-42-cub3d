/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:29:36 by dtheron           #+#    #+#             */
/*   Updated: 2025/05/06 16:08:13 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	freemapcopy(t_map *map)
{
	int	i;

	i = 0;
	while (map->mapcopy[i])
	{
		free(map->mapcopy[i]);
		i++;
	}
	free(map->mapcopy);
}

int	itstoolongsoimfindingsolution(t_map *map, int d, int i)
{
	checkifvisited(map);
	map->isgood = 0;
	if (map->mapcopy[d][i] == 32)
		return (1);
	else if (!floodfill(map, i, d))
	{
		freemapcopy(map);
		return (0);
	}
	return (1);
}

int	lookforproblem(t_map *map, t_cub *cub)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	(void)cub;
	if (!mapcopy(map))
		return (0);
	while (map->mapcopy[d])
	{
		i = 0;
		while (map->map[d][i])
		{
			if (!itstoolongsoimfindingsolution(map, d, i))
				return (0);
			i++;
		}
		d++;
	}
	freemapcopy(map);
	return (1);
}

int	itsalsotoolongsoinfindsolution(t_map *map, t_cub *cub, int d, int i)
{
	if (map->map[d][i] == 32 || map->map[d][i] == WALL)
		return (1);
	else if (map->map[d][i] == VOID)
	{
		if (checkvoid(map, cub, d, i) == 0)
			return (0);
	}
	else if (map->map[d][i] >= 65 && map->map[d][i] <= 90)
	{
		if (map->checkplayer)
			return (0);
		if (checkvoid(map, cub, d, i) == 0)
			return (0);
		if (checkplayerdirection(map, cub, d, i) == 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	checkmap(t_map *map, t_cub *cub)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	resizemap(map, cub);
	while (map->map[d])
	{
		i = 0;
		while (map->map[d][i])
		{
			if (!itsalsotoolongsoinfindsolution(map, cub, d, i))
				return (0);
			i++;
		}
		d++;
	}
	if (!map->checkplayer)
		return (0);
	if (!lookforproblem(map, cub))
		return (0);
	return (1);
}
