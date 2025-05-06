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


int	ft_atoi(const char *str)
{
	int i;
	int result;
	int count_negative;
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
	int i;
	int d;

	d = 0;
	i = 0;
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
	int i;
	char *newstr;

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
	printf("size %d\n", ft_strlen(newstr));
	return (newstr);
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_doublestrlen(char **str)
{
	int d;

	d = 0;
	while (str[d])
		d++;
	return (d);
}

int	checkvoid(t_map *map, t_cub *cub, int d, int i)
{
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

int	mapcopy(t_map *map)
{
	int d;
	int i;

	d = 0;
	i = 0;
	map->sizemap = ft_doublestrlen(map->map);
	map->mapcopy = malloc(sizeof(char *) * map->sizemap + 1);
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
	int i;
	int d;

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

void	freemapcopy(t_map *map)
{
	int i;

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
	int i;
	int d;

	i = 0;
	d = 0;
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

int itsalsotoolongsoinfindsolution(t_map *map, t_cub *cub, int d, int i)
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
	int i;
	int d;

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
	while (map->file[d][i] == 32)
		i++;
	if (map->file[d][i] != '\0' && map->file[d][i] != '\n')
	{
		free(map->ptrtexture);
		return (0);
	}
	return (1);
}

int	putcolor(t_map *map, int i, int d)
{
	if (map->countcolor != 2)
	{
		free(map->rgb);
		return (0);
	}
	if (map->rgb[0] > 255 || map->rgb[1] > 255 || map->rgb[2] > 255 || map->rgb[0] < 0 || map->rgb[1] < 0
		|| map->rgb[2] < 0)
	{
		free(map->rgb);
		return (0);
	}
	map->color = (map->rgb[0] << 16) | (map->rgb[1] << 8) | map->rgb[2];
	free(map->rgb);
	return (1);
}

int checkcolor(t_map *map, int i, int d)
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
			break;
		map->countcolor++;
	}
	if (!putcolor(map, i, d))
		return (0);
	return (1);
}

int north(t_map *map, t_cub *cub, int i, int d)
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

int south(t_map *map, t_cub *cub, int i, int d)
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

int west(t_map *map, t_cub *cub, int i, int d)
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

int east(t_map *map, t_cub *cub, int i, int d)
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

int color(t_map *map, t_cub *cub, int i, int d)
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

int	getinfo(t_map *map, t_cub *cub, int i, int d)
{
	if (map->file[d][i] == 'N' && map->file[d][i + 1] == 'O')
	{
		if (!north(map, cub, i, d))
			return (0);
	}
	else if (map->file[d][i] == 'S' && map->file[d][i + 1] == 'O')
	{
		if (!south(map, cub, i, d))
			return (0);
	}
	else if (map->file[d][i] == 'W' && map->file[d][i + 1] == 'E')
	{
		if (!west(map, cub, i, d))
			return (0);
	}
	else if (map->file[d][i] == 'E' && map->file[d][i + 1] == 'A')
	{
		if (!east(map, cub, i, d))
			return (0);
	}
	else 
		if (!color(map, cub, i, d))
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
		while (map->file[d][i])
		{
			printf("%s\n", map->file[d]);
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
	map->checkplayer = 0;
	if (map->count > 200)
	{
		printf("Error\n");
		printf("Map is too big !\n");
		return (0);
	}
	if (!checkfile(map, cub))
	{
		printf("Errori\n");
		return (0);
	}
	if (!checkmap(map, cub))
	{
		printf("Errore\n");
		return (0);
	}
	return (1);
}
