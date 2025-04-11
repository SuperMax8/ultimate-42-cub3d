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
#include "ft_printf.h"


int ft_strlen(char *str)
{
	int i;

	while (str[i])
		i++;
	return (i);
}
int ft_doublestrlen(char **str)
{
	int d;

	d = 0;
	while (str[d])
		d++;
	return (d);
}

int checkwall(t_map *map, t_cub *cub, int d, int i)
{
	if (i == 0 || i == ft_strlen(map->map[d]) - 1)
		return (0);
	if (d == 0 || d == ft_doublestrlen(map->map) - 1)
		return (0);
	if (map->map[d][i - 1] == 32 || map->map[d][i + 1] == 32)
		return (0);
	if (map->map[d + 1][i] == 32 || map->map[d - 1][i] == 32)
		return (0);
	return (1);
}
int	checkplayerdirection(t_map *map, t_cub *cub, int d, int i)
{
	if (map->map[d][i] == 'N')
	{
		map->x = i;
		map->y = d;
	}
	else if (map->map[d][i] == 'S')
	{
		map->x = i;
		map->y = d;
	}
	else if (map->map[d][i] == 'E')
	{
		map->x = i;
		map->y = d;
	}
	else if (map->map[d][i] == 'W')
	{
		map->x = i;
		map->y = d;
	}
	else 
		return (0);
	map->x = i;
	map->y = d;
	return (i);
}

int	checkmap(t_map *map, t_cub *cub)
{
	int i;
	int d;

	i = 0;
	d = 0;
	while (map->map[d])
	{
		i = 0;
		while (map->map[d][i])
		{
			if (map->map[d][i] == 32 || map->map[d][i] == WALL)
				continue;
			else if (map->map[d][i] == VOID)
			{
				if (checkwall(map, cub, d, i) == 0)
					return (0);
			}
			else if (map->map[d][i] >= 65 && map->map[d][i] <= 90)
			{
				if (checkplayerdirection(map , cub, i, d) == 0)
					return (0);
			}
			else 
				return (0);
			i++;
		}
		d++;
	}
	return (1);
}

int	copy(t_map *map, t_cub *cub, int i, int d)
{
	int e;

	e = 0;
	while (map->file[d][i] == 32 && map->file[d][i])
		i++;
	if (!map->file[d][i])
		return (0);
	while (map->file[d][i] && map->file[d][i] != 32)
	{
		map->ptrtexture[e] = map->file[d][i];
		i++;
		e++;
	}
	map->ptrtexture[e] = '\0';
	return (1);
}
int	getinfo(t_map *map, t_cub *cub, int i, int d)
{
	if (map->file[d][i] == 'N' && map->file[d][i + 1] == 'O')
	{
		i += 2;
		map->ptrtexture = map->texturenorth;
		if (map->texturenorth)
			return (0);
		if (!copy(map, cub, i, d))
			return (0);
		return (1);
	}
	else if (map->file[d][i] == 'S' && map->file[d][i + 1] == 'O')
	{
		i += 2;
		map->ptrtexture = map->texturesouth;
		if (map->texturesouth)
			return (0);
		if (!copy(map, cub, i, d))
			return (0);
		return (1);
	}
	else if (map->file[d][i] == 'W' && map->file[d][i + 1] == 'E')
	{
		i += 2;
		map->ptrtexture = map->texturewest;
		if (map->texturewest)
			return (0);
		if (!copy(map, cub, i, d))
			return (0);
		return (1);
	}
	else if (map->file[d][i] == 'E' && map->file[d][i + 1] == 'A')
	{
		i += 2;
		map->ptrtexture = map->textureeast;
		if (map->textureeast)
			return (0);
		if (!copy(map, cub, i, d))
			return (0);
		return (1);
	}
	else if (map->file[d][i] == 'F')
	{
		if (cub->color_floor)
			return (0);
	}
	else if (map->file[d][i] == 'C')
	{
		if (cub->color_ceiling)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	checkallfileinfo(t_cub *cub, t_map *map)
{
	if (map->texturenorth && map->texturesouth && map->textureeast
		&& map->texturewest && cub->color_ceiling && cub->color_floor)
		return (1);
	return (0);
}

int	checkfile(t_map *map, t_cub *cub)
{
	int i;
	int d;

	d = 0;
	i = 0;
	while (map->file[d])
	{
		i = 0;
		while (map->file[d][i] != '\n')
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
	if (map->count > 150 || ft_strlen(map->map[0]) > 300)
	{
		ft_printf("Error\n");
		ft_printf("Map is too big !\n");
		return (0);
	}
	if (!checkfile(map, cub))
	{
		ft_printf("Error\n");
		return (0);
	}
	if (!checkmap(map, cub))
	{
		ft_printf("Error\n");
		return (0);
	}
	return (1);
}
