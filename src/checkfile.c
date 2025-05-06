/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:29:30 by dtheron           #+#    #+#             */
/*   Updated: 2025/05/06 15:31:06 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	north(t_map *map, t_cub *cub, int i, int d)
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

int	south(t_map *map, t_cub *cub, int i, int d)
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

int	west(t_map *map, t_cub *cub, int i, int d)
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

int	east(t_map *map, t_cub *cub, int i, int d)
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
	else if (!color(map, cub, i, d))
		return (0);
	return (1);
}
