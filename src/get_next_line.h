/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:19:23 by mrotceig          #+#    #+#             */
/*   Updated: 2025/02/07 17:40:20 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct gnlfile
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	int		buffer_pos;
	int		buffer_size;
	char	*line;
	int		lcapacity;
	int		lsize;
}			t_GNLFile;

typedef struct strappendparams
{
	char	*source;
	char	*dest;
	int		source_start;
	int		source_end;
	int		dest_at;
}			t_StrAppendParams;

int			appendline(t_GNLFile *file, char *source, int from, int to);

int			indexof(char c, char *s, int from, int to);

char		*get_next_line(int fd);

#endif // GET_NEXT_LINE_H