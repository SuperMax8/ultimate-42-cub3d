/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:27 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/11 19:38:14 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define FOV 90

void	drawpixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < cub->win_res.x && y >= 0 && y < cub->win_res.y)
	{
		dst = cub->framebuff.addr + (y * cub->framebuff.line_length + x
				* (cub->framebuff.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	fillcolor(t_cub *cub, int color)
{
	int	y;
	int	x;

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

void	renderframe(t_cub *cub)
{
	int	x;
    float rayangle;

	fillcolor(cub, 0);
	while (x < cub->win_res.x)
	{
        rayangle = (x / (float) cub->win_res.x * FOV * 2) - FOV;
        rayangle = fmod(fmod(rayangle + cub->pyaw, 360.0f) + 360.0f, 360.0f);
        
		x++;
	}
}
