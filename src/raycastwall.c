/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastwall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:57:08 by mrotceig          #+#    #+#             */
/*   Updated: 2025/05/06 16:56:51 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define RENDER_DISTANCE 30

void	init(t_vec2f raydir, t_cub *cub, t_raycastwall *ray)
{
	ray->mapx = (int)cub->ploc.x;
	ray->mapy = (int)cub->ploc.y;
	ray->delta_distx = fabs(1.0f / raydir.x);
	ray->delta_disty = fabs(1.0f / raydir.y);
	ray->hit = false;
	if (raydir.x < 0)
	{
		ray->stepx = -1;
		ray->side_distx = (cub->ploc.x - ray->mapx) * ray->delta_distx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_distx = (ray->mapx + 1.0f - cub->ploc.x) * ray->delta_distx;
	}
	if (raydir.y < 0)
	{
		ray->stepy = -1;
		ray->side_disty = (cub->ploc.y - ray->mapy) * ray->delta_disty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_disty = (ray->mapy + 1.0f - cub->ploc.y) * ray->delta_disty;
	}
}

int	itr(t_cub *cub, t_raycastwall *ray)
{
	while (!ray->hit)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (ray->i > RENDER_DISTANCE)
			return (-1);
		ray->i++;
		if (ray->mapx < 0 || ray->mapx >= cub->mwidth || ray->mapy < 0
			|| ray->mapy >= cub->mheight)
			continue ;
		if (cub->map[ray->mapy][ray->mapx] == WALL)
			ray->hit = true;
	}
	return (1);
}

void	calcface(t_raycastwall *ray)
{
	if (ray->side == 0)
	{
		if (ray->stepx > 0)
			ray->result->face = WEST;
		else
			ray->result->face = EAST;
	}
	else
	{
		if (ray->stepy > 0)
			ray->result->face = NORTH;
		else
			ray->result->face = SOUTH;
	}
}

/**
 * Raycast for walls and return the hit position if wall found or NULL
 */
t_rayresult	*raycastwall(t_cub *cub, t_vec2f raydir)
{
	t_raycastwall	ray;

	init(raydir, cub, &ray);
	ray.i = 0;
	if (itr(cub, &ray) == -1)
		return (NULL);
	if (ray.side == 0)
		ray.distance = (ray.mapx - cub->ploc.x + (1 - ray.stepx) / 2.0f)
			/ raydir.x;
	else
		ray.distance = (ray.mapy - cub->ploc.y + (1 - ray.stepy) / 2.0f)
			/ raydir.y;
	ray.result = malloc(sizeof(t_rayresult));
	if (!ray.result)
		return (NULL);
	ray.result->hit.x = cub->ploc.x + raydir.x * ray.distance;
	ray.result->hit.y = cub->ploc.y + raydir.y * ray.distance;
	calcface(&ray);
	return (ray.result);
}
