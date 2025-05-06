/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:29:42 by dtheron           #+#    #+#             */
/*   Updated: 2025/05/06 16:10:05 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	putcolor(t_map *map)
{
	if (map->countcolor != 2)
	{
		free(map->rgb);
		return (0);
	}
	if (map->rgb[0] > 255 || map->rgb[1] > 255 || map->rgb[2] > 255
		|| map->rgb[0] < 0 || map->rgb[1] < 0 || map->rgb[2] < 0)
	{
		free(map->rgb);
		return (0);
	}
	map->color = (map->rgb[0] << 16) | (map->rgb[1] << 8) | map->rgb[2];
	free(map->rgb);
	return (1);
}

int	checkcolor(t_map *map, int i, int d)
{
	map->rgb[map->countcolor] = ft_atoi(map->file[d] + i);
	while (map->file[d][i] == 32)
		i++;
	if (map->file[d][i] == '-' || map->file[d][i] == '+')
		i++;
	while (map->file[d][i] >= '0' && map->file[d][i] <= '9')
		i++;
	while (map->file[d][i] == 32)
		i++;
	return (i);
}

int	stockagecolor(t_map *map, t_cub *cub, int i, int d)
{
	(void)cub;
	map->rgb = malloc(sizeof(int) * 3);
	if (!map->rgb)
		return (0);
	while (map->file[d][i] && map->countcolor < 3)
	{
		i = checkcolor(map, i, d);
		if (map->file[d][i] == ',')
			i++;
		else if (map->countcolor == 2 && map->file[d][i])
		{
			free(map->rgb);
			return (0);
		}
		else
			break ;
		map->countcolor++;
	}
	if (!putcolor(map))
		return (0);
	return (1);
}

int	color(t_map *map, t_cub *cub, int i, int d)
{
	map->countcolor = 0;
	if (map->file[d][i] == 'F')
	{
		i += 1;
		if (cub->color_floor)
			return (0);
		if (!stockagecolor(map, cub, i, d))
			return (0);
		cub->color_floor = map->color;
		return (1);
	}
	else if (map->file[d][i] == 'C')
	{
		i += 1;
		if (cub->color_ceiling)
			return (0);
		if (!stockagecolor(map, cub, i, d))
			return (0);
		cub->color_ceiling = map->color;
		return (1);
	}
	else
		return (0);
	return (0);
}
