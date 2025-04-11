/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheron <dtheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:58:20 by dtheron           #+#    #+#             */
/*   Updated: 2025/01/17 17:14:49 by dtheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s = (const char *)src;

	i = 0;
	if (!dest || !src)
		return (NULL);
	d = (char *)dest;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

size_t	gnl_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	gnl_strchr(const char *s, int c, int index)
{
	if (!s)
		return (-1);
	while (s[index])
	{
		if (s[index] == (char)c)
			return (index);
		index++;
	}
	return (-1);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	if (s1)
		gnl_memcpy(result, s1, len1);
	if (s2)
		gnl_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	free(s1);
	return (result);
}

char	*gnl_strsub(const char *s, int start, int end)
{
	char	*dup;
	int		i;

	i = 0;
	if (!s || start >= end)
		return (NULL);
	dup = malloc(end - start + 1);
	if (!dup)
		return (NULL);
	while (start < end)
		dup[i++] = s[start++];
	dup[i] = '\0';
	return (dup);
}
