/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:57:46 by mrotceig          #+#    #+#             */
/*   Updated: 2024/11/10 17:22:04 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	indexof(char c, char *s, int from, int to)
{
	int	i;

	i = from;
	while (i < to)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	strappend(t_StrAppendParams *params)
{
	int	i;
	int	pos;

	i = params->source_start;
	pos = params->dest_at;
	while (i < params->source_end)
	{
		params->dest[pos] = params->source[i];
		i++;
		pos++;
	}
}

void	resizeln(t_GNLFile *file)
{
	char	*newline;
	int		newcap;
	int		i;

	newcap = file->lcapacity + BUFFER_SIZE;
	newline = malloc(sizeof(char) * newcap);
	if (!newline)
	{
		free(file->line);
		file->line = NULL;
		file->lsize = 0;
		file->buffer_pos = 0;
		file->buffer_size = 0;
		return ;
	}
	i = 0;
	while (i < file->lsize)
	{
		newline[i] = file->line[i];
		i++;
	}
	free(file->line);
	file->line = newline;
	file->lcapacity = newcap;
}

int	appendline(t_GNLFile *file, char *source, int from, int to)
{
	int					addsize;
	t_StrAppendParams	params;

	addsize = to - from;
	if (file->lsize + addsize >= file->lcapacity)
	{
		resizeln(file);
		if (file->line == NULL)
			return (0);
	}
	params.source = source;
	params.dest = file->line;
	params.source_start = from;
	params.source_end = to;
	params.dest_at = file->lsize;
	strappend(&params);
	file->lsize += addsize;
	return (1);
}
