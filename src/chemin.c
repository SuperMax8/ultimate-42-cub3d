/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chemin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/02/07 15:24:59 by dtheron           #+#    #+#             */
/*   Updated: 2025/02/07 15:24:59 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	copy(t_map *map, t_cub *cub, int i, int d)
{
	int	e;

	e = 0;
	while (map->file[d][i] == 32 && map->file[d][i])
		i++;
	if (!map->file[d][i])
		return (0);
	map->ptrtexture = malloc(sizeof(char) * ft_strlen(map->file[d] + i) + 1);
	if (!map->ptrtexture)
		return (0);
	while (map->file[d][i] && map->file[d][i] != 32 && map->file[d][i] != '\n')
	{
		map->ptrtexture[e] = map->file[d][i];
		i++;
		e++;
	}
	map->ptrtexture[e] = '\0';
	while (map->file[d][i] == 32)
		i++;
	if (map->file[d][i] != '\0' && map->file[d][i] != '\n')
	{
		free(map->ptrtexture);
		return (0);
	}
	return (1);
}

int	checkallfileinfo(t_cub *cub, t_map *map)
{
	if (map->texturenorth && map->texturesouth && map->textureeast
		&& map->texturewest && cub->color_ceiling && cub->color_floor)
		return (1);
	return (0);
}

int	checkfile(t_map *map, t_cub *cub, int i, int d)
{
	while (map->file[d])
	{
		i = 0;
		while (map->file[d][i])
		{
			if (map->file[d][i] >= 65 && map->file[d][i] <= 90)
			{
				if (getinfo(map, cub, i, d))
					break ;
				else
					return (0);
			}
			if (map->file[d][i] != 32)
				return (0);
			i++;
		}
		d++;
		if (checkallfileinfo(cub, map))
		{
			map->map = map->file + d;
			return (1);
		}
	}
	return (0);
}

int	ismapvalid(t_map *map, t_cub *cub)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	map->checkplayer = 0;
	if (map->count > 200)
	{
		printf("Error\n");
		printf("Map is too big !\n");
		return (0);
	}
	if (!checkfile(map, cub, i, d))
	{
		printf("Error\n");
		return (0);
	}
	if (!checkmap(map, cub))
	{
		printf("Error\n");
		return (0);
	}
	return (1);
}
