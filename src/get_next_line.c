/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:53:03 by mrotceig          #+#    #+#             */
/*   Updated: 2024/11/26 20:45:08 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_GNLFile	*getgnl(int fd)
{
	static t_GNLFile	file = {-1, {}, 0, 0, NULL, 0, 0};

	if (file.fd != fd)
	{
		file.fd = fd;
		file.buffer_pos = 0;
		file.buffer_size = 0;
	}
	file.lsize = 0;
	file.lcapacity = BUFFER_SIZE + 1;
	file.line = malloc(sizeof(char) * (file.lcapacity));
	if (!file.line)
		return (NULL);
	return (&file);
}

int	refill_buffer(int fd, t_GNLFile *file)
{
	file->buffer_size = read(fd, file->buffer, BUFFER_SIZE);
	if (file->buffer_size == -1)
	{
		file->buffer_size = 0;
		file->buffer_pos = 0;
		file->lsize = 0;
		return (-1);
	}
	file->buffer_pos = 0;
	return (file->buffer_size);
}

int	process_line(t_GNLFile *file)
{
	int	ni;

	ni = indexof('\n', file->buffer, file->buffer_pos, file->buffer_size);
	if (ni != -1)
	{
		if (!appendline(file, file->buffer, file->buffer_pos, ni + 1))
			return (-1);
		file->buffer_pos = ni + 1;
		file->line[file->lsize] = '\0';
		return (1);
	}
	if (!appendline(file, file->buffer, file->buffer_pos, file->buffer_size))
		return (-1);
	file->buffer_pos = 0;
	return (0);
}

char	*checkend(t_GNLFile *file)
{
	if (file->lsize > 0)
	{
		file->line[file->lsize] = '\0';
		return (file->line);
	}
	if (file->line)
	{
		free(file->line);
		file->line = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	t_GNLFile	*file;
	int			result;

	file = getgnl(fd);
	if (!file)
		return (NULL);
	while (1)
	{
		if (file->buffer_size > 0 && file->buffer_pos < file->buffer_size)
		{
			result = process_line(file);
			if (result == -1)
				return (NULL);
			if (result == 1)
				return (file->line);
		}
		if (refill_buffer(fd, file) <= 0)
			break ;
	}
	return (checkend(file));
}

// int	main(int count, char **args)
// {
// 	int fd;
// 	char *line;
// 	char *RED;
// 	char *RESET;
// 	int i;

// 	RED = "\033[1;31m";
// 	RESET = "\033[0m";
// 	for (int a = 1; a < count; ++a)
// 	{
// 		printf("%sStartFile : %s\n", RESET, args[a]);
// 		fd = open(args[a], O_RDONLY);
// 		i = 0;
// 		while ((line = get_next_line(fd)) != NULL)
// 		{
// 			printf("%s%s", RED, line);
// 			free(line);
// 			i++;
// 		}
// 		printf("%sENDFILE\n", RESET);
// 		close(fd);
// 	}
// }