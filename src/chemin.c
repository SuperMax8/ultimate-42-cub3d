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

void	resizemap(t_map *map, t_cub *cub)
{
	int i;
	int d;

	d = 0;
	i = 0;
	while(map->map[d])
	{
		i = 0;
		while(map->map[d][i])
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

char *ft_strdups(char *str)
{
	int i;
	char *newstr;

	i = 0;
	newstr = malloc((sizeof(char) * ft_strlen(str)) + 1);
	if (!newstr)
		return (NULL);
	while(str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
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
	if (map->map[d][i] == NORTH)
	{
		map->x = i;
		map->y = d;
	}
	else if (map->map[d][i] == SOUTH)
	{
		map->x = i;
		map->y = d;
	}
	else if (map->map[d][i] == EAST)
	{
		map->x = i;
		map->y = d;
	}
	else if (map->map[d][i] == WEST)
	{
		map->x = i;
		map->y = d;
	}
	else 
		return (0);
	return (1);
}

int	checkmap(t_map *map, t_cub *cub)
{
	int i;
	int d;
	int checkplayer;

	i = 0;
	d = 0;
	checkplayer = 0;
	resizemap(map, cub);
	while (map->map[d])
	{
		i = 0;
		printf("%s\n", map->map[d]);
		while (map->map[d][i])
		{
			if (map->map[d][i] == 32 || map->map[d][i] == WALL)
			{
				i++;
				continue;
			}
			else if (map->map[d][i] == VOID)
			{
				if (checkwall(map, cub, d, i) == 0)
					return (0);
			}
			else if (map->map[d][i] >= 65 && map->map[d][i] <= 90)
			{
				if (checkplayer)
					return (0);
				if (checkwall(map, cub, d, i) == 0)
					return (0);
				if (checkplayerdirection(map , cub, d, i) == 0)
					return (0);
				checkplayer = 1;
			}
			else 
				return (0);
			i++;
		}
		d++;
	}
	if (!checkplayer)
		return (0);
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
	return (1);
}
int	getinfo(t_map *map, t_cub *cub, int i, int d)
{
	if (map->file[d][i] == 'N' && map->file[d][i + 1] == 'O')
	{
		i += 2;
		if (map->texturenorth)
			return (0);
		if (!copy(map, cub, i, d))
			return (0);
		map->texturenorth = ft_strdups(map->ptrtexture);
		printf("%s\n", map->texturenorth);
		free(map->ptrtexture);
		return (1);
	}
	else if (map->file[d][i] == 'S' && map->file[d][i + 1] == 'O')
	{
		i += 2;
		if (map->texturesouth)
			return (0);
		if (!copy(map, cub, i, d))
			return (0);
		map->texturesouth = ft_strdups(map->ptrtexture);
		free(map->ptrtexture);
		return (1);
	}
	else if (map->file[d][i] == 'W' && map->file[d][i + 1] == 'E')
	{
		i += 2;
		if (map->texturewest)
			return (0);
		if (!copy(map, cub, i, d))
			return (0);
		map->texturewest = ft_strdups(map->ptrtexture);
		free(map->ptrtexture);
		return (1);
	}
	else if (map->file[d][i] == 'E' && map->file[d][i + 1] == 'A')
	{
		i += 2;
		if (map->textureeast)
			return (0);
		if (!copy(map, cub, i, d))
			return (0);
		map->textureeast = ft_strdups(map->ptrtexture);
		free(map->ptrtexture);
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
		&& map->texturewest)
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
			printf("%s", map->file[d]);
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
	if (map->count > 150)
	{
		printf("Error\n");
		printf("Map is too big !\n");
		return (0);
	}
	if (!checkfile(map, cub))
	{
		printf("Error\n");
		return (0);
	}
	if (!checkmap(map, cub))
	{
		printf("Errore\n");
		return (0);
	}
	return (1);
}
