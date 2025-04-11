/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:01:07 by dtheron           #+#    #+#             */
/*   Updated: 2025/01/17 17:20:48 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_gnl
{
	char	*buffer;
	size_t	size;
	size_t	index;
	int		fd;
}			t_gnl;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void		*gnl_memcpy(void *dest, const void *src, size_t n);
size_t		gnl_strlen(const char *str);
int			gnl_strchr(const char *s, int c, int d);
char		*gnl_strjoin(char *s1, char *s2);
char		*gnl_strsub(const char *s, int start, int end);
char		*get_next_line(int fd);

#endif
