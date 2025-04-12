/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:28:01 by dtheron           #+#    #+#             */
/*   Updated: 2025/04/12 03:35:35 by max              ###   ########.fr       */
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
}

int	checkcub(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] != 'b' || str[i - 1] != 'u' || str[i - 2] != 'c' || str[i - 3] != '.')
		return (1);
	return(0);
}

int	main(int count, char **args)
{
	static t_map		map;
	static t_cub		cub;
	if (count != 2)
	{
		printf("not the right number of args");
		return (0);
	}
	if (checkcub(args[1]))
	{
		printf("its not a *.cub file");
		return (0);
	}
	map.fd = open(args[1], O_RDONLY);
	if (map.fd < 0)
		return (0);
	map.count = count_line(&map);
	parsing(&map);
	int d = 0;
	while (map.file[d])
	{
		printf("%s", map.file[d]);
		d++;
	}
	close(map.fd);
	printf("error");
	if (!ismapvalid(&map, &cub))
	{
		free_file(&map);
		return (0);
	}
	//mini(map);
	printf("Error\n");
	return (1);
}
