/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:27 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/12 05:51:42 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define FOV 75

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

int darken_color(int color, float factor)
{
	if (factor < 0.0f)
		factor = 0.0f;
	if (factor > 1.0f)
		factor = 1.0f;

	int t = (color >> 24) & 0xFF;
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;

	r = (int)(r * factor);
	g = (int)(g * factor);
	b = (int)(b * factor);

	return create_trgb(t, r, g, b);
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
			drawpixel(cub->framebuff, coord.x + i, coord.y + j, color);
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
			drawpixel(cub->framebuff, x, y, color);
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
			drawpixel(cub->framebuff, x, y, color);
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
			drawpixel(cub->framebuff, x + xywh[0], y + xywh[1], color);
			x++;
		}
		y++;
	}
}

void renderwall(t_cub *cub, int screencol, t_rayresult *ray)
{
	float sizeper;
	int ysize;
	int y;
	int yend;
	t_img *texture;
	float worldcol;
	float colper;
	int texturecol;
	float dist;
	int wallheight;
	int i;
	float brightness = 0;

	dist = cos(toradian(ray->rayangle - cub->pyaw)) * distance(cub->ploc, ray->hit);
	sizeper = 1 / dist + 0.0001f;
	if (sizeper <= 0)
		return;
	ysize = cub->win_res.y * sizeper;
	y = cub->win_res.y / 2 - ysize / 2;
	yend = cub->win_res.y / 2 + ysize / 2;
	if (ray->face == NORTH)
	{
		texture = cub->img_n;
		worldcol = ray->hit.x;
		brightness = 1;
	}
	else if (ray->face == SOUTH)
	{
		texture = cub->img_s;
		worldcol = ray->hit.x;
		brightness = 0.65;
	}
	else if (ray->face == WEST)
	{
		texture = cub->img_w;
		worldcol = ray->hit.y;
		brightness = 0.75;
	}
	else if (ray->face == EAST)
	{
		texture = cub->img_e;
		worldcol = ray->hit.y;
		brightness = 0.9;
	}
	colper = worldcol - ((int)worldcol);
	texturecol = texture->width * colper;
	wallheight = yend - y;

	int lastty = -1;
	int color;
	i = 0;
	while (i < wallheight)
	{
		int ty = (i / (float)wallheight) * texture->height;
		if (lastty != ty)
		{
			color = getpixel(texture, texturecol, ty);
			color = darken_color(color, brightness);
			lastty = ty;
		}
		drawpixel(cub->framebuff, screencol, y + i, color);
		i++;
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
			result->face = WEST;
		else
			result->face = EAST;
	}
	else
	{
		if (stepY > 0)
			result->face = NORTH;
		else
			result->face = SOUTH;
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
			if (cub->map[y][x] == WALL)
				drawsqare(cub, coord, 20, 0x00FF0000);
			else if (cub->map[y][x] == VOID)
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

	fillvgradient(cub, create_trgb(255, 52, 171, 235), create_trgb(255, 16, 80, 176), (int[]){0, 0, cub->win_res.x, cub->win_res.y / 2});
	fillvgradient(cub, create_trgb(255, 9, 107, 41), create_trgb(255, 36, 224, 48), (int[]){0, cub->win_res.y / 2, cub->win_res.x, cub->win_res.y / 2});
	printmap(cub);
	x = 0;
	while (x < cub->win_res.x)
	{
		rayangle = (x / (float)cub->win_res.x * FOV) - FOV / 2;
		rayangle = normyaw(rayangle + cub->pyaw);
		raydir = yawtovec(rayangle);
		ray = raycastwall(cub, raydir);
		if (ray)
		{
			ray->rayangle = rayangle;
			renderwall(cub, x, ray);
			free(ray);
		}
		x++;
	}
}
