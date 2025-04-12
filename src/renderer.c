/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:27 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/12 03:09:29 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define FOV 70

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

int lerp_color(int color1, int color2, float f)
{
	int t1 = (color1 >> 24) & 0xFF;
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = (color1) & 0xFF;

	int t2 = (color2 >> 24) & 0xFF;
	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = (color2) & 0xFF;

	int t = (int)lerp((float)t1, (float)t2, f);
	int r = (int)lerp((float)r1, (float)r2, f);
	int g = (int)lerp((float)g1, (float)g2, f);
	int b = (int)lerp((float)b1, (float)b2, f);

	return create_trgb(t, r, g, b);
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

void fillvgradient(t_cub *cub, int color1, int color2, int *xywh)
{
	int y;
	int x;
	int color;

	y = 0;
	while (y < xywh[3])
	{
		x = 0;
		color = lerp_color(color1, color2, y / (float)xywh[2]);
		while (x < xywh[2])
		{
			drawpixel(cub, x + xywh[0], y + xywh[1], color);
			x++;
		}
		y++;
	}
}

void renderwall(t_cub *cub, int collumn, float distance, char face)
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
	int color;
	if (face == 'N')
		color = create_trgb(0, 255, 0, 0);
	else if (face == 'S')
		color = create_trgb(0, 0, 255, 0);
	else if (face == 'W')
		color = create_trgb(0, 255, 0, 255);
	else if (face == 'E')
		color = create_trgb(0, 0, 255, 255);
	while (y < yend)
	{
		drawpixel(cub, collumn, y, color);
		y++;
	}
}

/**
 * Raycast for walls and return the hit position if wall found or NULL
 */
t_rayresult *raycastwall(t_cub *cub, t_vec2f raydir)
{
	int mapX = (int)cub->ploc.x;
	int mapY = (int)cub->ploc.y;

	float deltaDistX = fabs(1.0f / raydir.x);
	float deltaDistY = fabs(1.0f / raydir.y);

	int stepX;
	int stepY;
	float sideDistX;
	float sideDistY;

	int hit = 0;
	int side;

	if (raydir.x < 0)
	{
		stepX = -1;
		sideDistX = (cub->ploc.x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0f - cub->ploc.x) * deltaDistX;
	}

	if (raydir.y < 0)
	{
		stepY = -1;
		sideDistY = (cub->ploc.y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0f - cub->ploc.y) * deltaDistY;
	}
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (mapX < 0 || mapX >= cub->mwidth || mapY < 0 || mapY >= cub->mheight)
			return (NULL);
		if (cub->map[mapY][mapX] == '1')
			hit = 1;
	}
	float distance;
	if (side == 0)
		distance = (mapX - cub->ploc.x + (1 - stepX) / 2.0f) / raydir.x;
	else
		distance = (mapY - cub->ploc.y + (1 - stepY) / 2.0f) / raydir.y;

	t_rayresult *result = malloc(sizeof(t_rayresult));
	if (!result)
		return (NULL);
	result->hit.x = cub->ploc.x + raydir.x * distance;
	result->hit.y = cub->ploc.y + raydir.y * distance;
	if (side == 0)
	{
		if (stepX > 0)
			result->face = 'W';
		else
			result->face = 'E';
	}
	else
	{
		if (stepY > 0)
			result->face = 'N';
		else
			result->face = 'S';
	}
	return (result);
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

/**
 * Render the frame on the buffer img
 */
void renderframe(t_cub *cub)
{
	int x;
	float rayangle;
	t_vec2f raydir;
	t_rayresult *ray;
	float dist;
	float angle_diff;
	float corrected_dist;

	fillvgradient(cub, create_trgb(255, 52, 171, 235), create_trgb(255, 16, 80, 176), (int[]){0, 0, cub->win_res.x, cub->win_res.y / 2});
	fillvgradient(cub, create_trgb(255, 9, 107, 41), create_trgb(255, 36, 224, 48), (int[]){0, cub->win_res.y / 2, cub->win_res.x, cub->win_res.y / 2});
	printmap(cub);
	x = 0;
	while (x < cub->win_res.x)
	{
		rayangle = (x / (float)cub->win_res.x * FOV) - FOV / 2;
		rayangle = fmod(fmod(rayangle + cub->pyaw, 360.0f) + 360.0f, 360.0f);
		raydir = yawtovec(rayangle);
		ray = raycastwall(cub, raydir);
		if (ray)
		{
			angle_diff = toradian(rayangle - cub->pyaw);
			corrected_dist = cos(angle_diff) * distance(cub->ploc, ray->hit);
			renderwall(cub, x, corrected_dist, ray->face);
			free(ray);
		}
		x++;
	}
}
