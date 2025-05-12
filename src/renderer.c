/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:27 by mrotceig          #+#    #+#             */
/*   Updated: 2025/05/12 16:47:53 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define FOV 75

void	printmapplayer(t_cub *cub)
{
	t_vec2f	dir;

	drawsqare(cub, (t_vec2){cub->ploc.x * 20 - 5, cub->ploc.y * 20 - 5}, 10,
		0x00FF00FF);
	dir = yawtovec(cub->pyaw);
	drawsqare(cub, (t_vec2){cub->ploc.x * 20 + dir.x * 10 - 2.5, cub->ploc.y
		* 20 + dir.y * 10 - 2.5}, 5, 0x00FF00FF);
}

void	printmap(t_cub *cub)
{
	int		y;
	int		x;
	t_vec2	coord;

	y = 0;
	while (y < cub->mheight)
	{
		x = 0;
		while (x < cub->mwidth)
		{
			coord.x = x * 20;
			coord.y = y * 20;
			if (cub->map[y][x] == '\0')
				break ;
			if (cub->map[y][x] == WALL)
				drawsqare(cub, coord, 20, 0x00FF0000);
			else if (cub->map[y][x] == VOID)
				drawsqare(cub, coord, 20, 0x00043200);
			x++;
		}
		y++;
	}
	printmapplayer(cub);
}

/**
 * Render the frame on the buffer img
 */
void	renderframe(t_cub *cub)
{
	register int			x;
	register float			rayangle;
	register t_vec2f		raydir;
	register t_rayresult	*ray;

	fillvgradient(cub, cub->color_ceiling, darken_color(cub->color_ceiling,
			0.4), (int []){0, 0, cub->win_res.x, cub->win_res.y / 2});
	fillvgradient(cub, darken_color(cub->color_floor, 0.4), cub->color_floor,
		(int []){0, cub->win_res.y / 2, cub->win_res.x, cub->win_res.y / 2});
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
	printmap(cub);
}
