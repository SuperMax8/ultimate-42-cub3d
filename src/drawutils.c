/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:42:05 by mrotceig          #+#    #+#             */
/*   Updated: 2025/05/06 15:42:11 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	drawsqare(t_cub *cub, t_vec2 coord, int size, int color)
{
	register int	i;
	register int	j;

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

void	fillfloor(t_cub *cub, int color)
{
	register int	y;
	register int	x;

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

void	fillcolor(t_cub *cub, int color)
{
	register int	y;
	register int	x;

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

void	fillvgradient(t_cub *cub, int color1, int color2, int *xywh)
{
	register int	y;
	register int	x;
	int				color;

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
