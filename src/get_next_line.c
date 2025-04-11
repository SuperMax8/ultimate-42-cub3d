/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:01:11 by dtheron           #+#    #+#             */
/*   Updated: 2025/01/17 17:24:01 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_gnl(t_gnl *gnl)
{
	if (gnl->buffer)
	{
		free(gnl->buffer);
		gnl->buffer = NULL;
	}
	gnl->fd = -1;
	gnl->index = 0;
	gnl->size = 0;
}

static void	free_lereste(t_gnl *gnl, char *temp)
{
	free(temp);
	free_gnl(gnl);
}

static char	*read_to_buffer(t_gnl *gnl, char *temp, int bytes_read)
{
	while (gnl_strchr(gnl->buffer, '\n', gnl->index) == -1)
	{
		bytes_read = read(gnl->fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free_lereste(gnl, temp);
			return (NULL);
		}
		if (bytes_read == 0)
		{
			free(temp);
			return (gnl->buffer);
		}
		temp[bytes_read] = '\0';
		gnl->buffer = gnl_strjoin(gnl->buffer, temp);
		if (!gnl->buffer)
		{
			free_lereste(gnl, temp);
			return (NULL);
		}
		gnl->size = gnl_strlen(gnl->buffer);
	}
	free(temp);
	return (gnl->buffer);
}

static char	*extract_line(t_gnl *gnl, char *temp, int bytes_read)
{
	char	*line;
	int		newline_pos;

	gnl->buffer = read_to_buffer(gnl, temp, bytes_read);
	if (!gnl->buffer || gnl->size == 0 || gnl->index >= gnl->size)
	{
		free_gnl(gnl);
		return (NULL);
	}
	newline_pos = gnl_strchr(gnl->buffer, '\n', gnl->index);
	if (newline_pos == -1)
	{
		line = gnl_strsub(gnl->buffer, gnl->index, gnl->size);
		gnl->index = gnl->size;
	}
	else
	{
		line = gnl_strsub(gnl->buffer, gnl->index, newline_pos + 1);
		gnl->index = newline_pos + 1;
	}
	if (gnl->index >= gnl->size)
		free_gnl(gnl);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {NULL, 0, 0, -1};
	char			*temp;
	ssize_t			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 0;
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
	{
		free_gnl(&gnl);
		return (NULL);
	}
	if (gnl.fd != fd)
	{
		free_gnl(&gnl);
		gnl.fd = fd;
	}
	return (extract_line(&gnl, temp, bytes_read));
}

/*int	main(int argc, char **argv)
{
	int	fd;
	char	*line;
	int	i;

	i = 0;
	if (argc != 2)
	{
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}*/