/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:27 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/12 01:59:02 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define FOV 70

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void drawpixel(t_cub *cub, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < cub->win_res.x && y >= 0 && y < cub->win_res.y)
	{
		dst = cub->framebuff.addr + (y * cub->framebuff.line_length + x * (cub->framebuff.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void drawsqare(t_cub *cub, t_vec2 coord, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			drawpixel(cub, coord.x + i, coord.y + j, color);
			j++;
		}
		i++;
	}
}

void fillfloor(t_cub *cub, int color)
{
	int y;
	int x;

	y = cub->win_res.y / 2;
	while (y < cub->win_res.y)
	{
		x = 0;
		while (x < cub->win_res.x)
		{
			drawpixel(cub, x, y, color);
			x++;
		}
		y++;
	}
}

void fillcolor(t_cub *cub, int color)
{
	int y;
	int x;

	y = 0;
	while (y < cub->win_res.y)
	{
		x = 0;
		while (x < cub->win_res.x)
		{
			drawpixel(cub, x, y, color);
			x++;
		}
		y++;
	}
}

void renderwall(t_cub *cub, int collumn, float distance)
{
	float sizeper;
	int ysize;
	int y;
	int yend;

	sizeper = 1 / distance + 0.0001f;
	if (sizeper <= 0)
		return;
	ysize = cub->win_res.y * sizeper;
	y = cub->win_res.y / 2 - ysize / 2;
	yend = cub->win_res.y / 2 + ysize / 2;
	while (y < yend)
	{
		drawpixel(cub, collumn, y, 234543556);
		y++;
	}
}

/**
 * Raycast for walls and return the hit position if wall found or NULL
 */
t_vec2f *raycastwall(t_cub *cub, t_vec2f direction)
{
	float i;
	t_vec2f lastpos;
	t_vec2f pos;
	t_vec2f *val;
	bool hit;

	hit = false;
	i = 0;
	while (true)
	{
		pos.x = direction.x * i + cub->ploc.x;
		pos.y = direction.y * i + cub->ploc.y;
		drawpixel(cub, pos.x * 20, pos.y * 20, 3278079);
		if (i > 30)
			return (NULL);
		if (pos.x > 0 && pos.x < 5 && pos.y > 0 && pos.y < 5)
		{
			if (cub->map[(int)pos.y][(int)pos.x] == '1')
			{
				hit = true;
				break;
			}
			lastpos = pos;
		}
		i += 0.01;
	}
	if (i != 0 && hit)
	{
		val = malloc(sizeof(t_vec2f));
		val->x = lastpos.x;
		val->y = lastpos.y;
		return (val);
	}
	return (NULL);
}

void printmap(t_cub *cub)
{
	int y;
	int x;
	t_vec2 coord;
	t_vec2f dir;

	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			coord.x = x * 20;
			coord.y = y * 20;
			if (cub->map[y][x] == '1')
				drawsqare(cub, coord, 20, 0x00FF0000);
			else if (cub->map[y][x] == '0')
				drawsqare(cub, coord, 20, 0x00043200);
			x++;
		}
		y++;
	}
	drawsqare(cub, (t_vec2){cub->ploc.x * 20, cub->ploc.y * 20}, 10,
			  0x00FF00FF);
	dir = yawtovec(cub->pyaw);
	drawsqare(cub, (t_vec2){cub->ploc.x * 20 + dir.x * 10, cub->ploc.y * 20 + dir.y * 10}, 5, 0x00FF00FF);
}

void renderframe(t_cub *cub)
{
	int x;
	float rayangle;
	t_vec2f raydir;
	t_vec2f *wallpos;
	float dist;
	float angle_diff;
	float corrected_dist;

	fillcolor(cub, 0);
	fillfloor(cub, create_trgb(200, 0, 100, 50));
	printmap(cub);
	x = 0;
	while (x < cub->win_res.x)
	{
		rayangle = (x / (float)cub->win_res.x * FOV) - FOV / 2;
		rayangle = fmod(fmod(rayangle + cub->pyaw, 360.0f) + 360.0f, 360.0f);
		raydir = yawtovec(rayangle);
		wallpos = raycastwall(cub, raydir);
		if (wallpos)
		{
			angle_diff = toradian(rayangle - cub->pyaw);
			corrected_dist = cos(angle_diff) * distance(cub->ploc, *wallpos);
			renderwall(cub, x, corrected_dist);
		}
		x++;
	}
}
