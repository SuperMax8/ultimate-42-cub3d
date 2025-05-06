/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:28:01 by dtheron           #+#    #+#             */
/*   Updated: 2025/05/06 16:11:16 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <fcntl.h>

void	free_file(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->count)
		free(map->file[i++]);
	free(map->file);
	free(map->textureeast);
	free(map->texturenorth);
	free(map->texturewest);
	free(map->texturesouth);
}

int	checkcub(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] != 'b' || str[i - 1] != 'u' || str[i - 2] != 'c' || str[i
			- 3] != '.')
		return (1);
	return (0);
}

int	triplelen(char **str)
{
	int	biggest;
	int	i;

	biggest = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) > biggest)
		{
			biggest = ft_strlen(str[i]);
		}
		i++;
	}
	return (biggest);
}

int	errorcheck(int count, char **args, t_map *map)
{
	if (count != 2)
	{
		printf("not the right number of args\n");
		return (0);
	}
	if (checkcub(args[1]))
	{
		printf("its not a *.cub file\n");
		return (0);
	}
	map->fd = open(args[1], O_RDONLY);
	if (map->fd < 0)
	{
		printf("file doesnt exist\n");
		return (0);
	}
	map->count = count_line(map);
	close(map->fd);
	return (1);
}

int	main(int count, char **args)
{
	static t_map	map;
	static t_cub	cub;

	cub.win_res.x = 16 * 100;
	cub.win_res.y = 9 * 100;
	if (!errorcheck(count, args, &map))
		return (0);
	map.fd = open(args[1], O_RDONLY);
	parsing(&map);
	close(map.fd);
	if (!ismapvalid(&map, &cub))
	{
		free_file(&map);
		return (0);
	}
	cub.mapmap = &map;
	cub.ploc.x = (float)map.x + 0.5f;
	cub.ploc.y = (float)map.y + 0.5f;
	cub.map = map.map;
	cub.mwidth = triplelen(map.map);
	cub.mheight = map.sizemap;
	initgraph(&cub);
	return (1);
}
