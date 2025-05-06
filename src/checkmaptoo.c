/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmaptoo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:29:40 by dtheron           #+#    #+#             */
/*   Updated: 2025/05/06 16:08:32 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	checkvoid(t_map *map, t_cub *cub, int d, int i)
{
	(void)cub;
	if (i == 0 || i == ft_strlen(map->map[d]) - 1)
		return (0);
	if (d == 0 || d == ft_doublestrlen(map->map) - 1)
		return (0);
	if (map->map[d][i - 1] == 32 || map->map[d][i - 1] == '\0' || map->map[d][i
		+ 1] == 32 || map->map[d][i + 1] == '\0')
		return (0);
	if (map->map[d + 1][i] == 32 || map->map[d + 1][i] == '\0' || map->map[d
		- 1][i] == 32 || map->map[d - 1][i] == '\0')
		return (0);
	return (1);
}

int	checkplayerdirection(t_map *map, t_cub *cub, int d, int i)
{
	(void)cub;
	if (map->map[d][i] == NORTH)
		cub->pyaw = 0;
	else if (map->map[d][i] == SOUTH)
		cub->pyaw = 180;
	else if (map->map[d][i] == EAST)
		cub->pyaw = 90;
	else if (map->map[d][i] == WEST)
		cub->pyaw = 270;
	else
		return (0);
	map->x = i;
	map->y = d;
	map->checkplayer = 1;
	return (1);
}
