/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:30:10 by dtheron           #+#    #+#             */
/*   Updated: 2025/05/12 16:30:12 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_next_line.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*new_str;

	if (!src)
		return (0);
	i = 0;
	while (src[i] != '\0')
		i++;
	new_str = malloc(i * sizeof(char) + 1);
	if (!new_str)
		return (0);
	ft_strcpy(new_str, src);
	return (new_str);
}

int	count_line(t_map *map)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(map->fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(map->fd);
	}
	return (count);
}

void	parsing(t_map *map)
{
	int	i;

	i = 0;
	map->file = malloc(sizeof(char *) * (map->count + 1));
	if (!map->file)
		return ;
	while (i < map->count)
	{
		map->file[i] = get_next_line(map->fd);
		if (map->file[i][ft_strlen(map->file[i]) - 1] == '\n')
			map->file[i][ft_strlen(map->file[i]) - 1] = '\0';
		i++;
	}
	map->file[i] = NULL;
}
