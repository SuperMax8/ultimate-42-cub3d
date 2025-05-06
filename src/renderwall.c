/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderwall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:47 by mrotceig          #+#    #+#             */
/*   Updated: 2025/05/06 16:32:53 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	setnorth(t_rayresult *ray, t_renderwall *renderwall, t_cub *cub)
{
	renderwall->texture = cub->img_n;
	renderwall->worldcol = ray->hit.x;
	renderwall->brightness = 1;
}

int	faces(t_rayresult *ray, t_renderwall *renderwall, t_cub *cub)
{
	if (ray->face == NORTH)
		setnorth(ray, renderwall, cub);
	else if (ray->face == SOUTH)
	{
		renderwall->texture = cub->img_s;
		renderwall->worldcol = ray->hit.x;
		renderwall->brightness = 0.65;
	}
	else if (ray->face == WEST)
	{
		renderwall->texture = cub->img_w;
		renderwall->worldcol = ray->hit.y;
		renderwall->brightness = 0.75;
	}
	else if (ray->face == EAST)
	{
		renderwall->texture = cub->img_e;
		renderwall->worldcol = ray->hit.y;
		renderwall->brightness = 0.9;
	}
	else
		return (-1);
	return (1);
}

void	drawwall(t_cub *cub, t_renderwall *renderwall, int screencol)
{
	renderwall->colper = renderwall->worldcol - ((int)renderwall->worldcol);
	renderwall->texturecol = renderwall->texture->width * renderwall->colper;
	renderwall->wallheight = renderwall->yend - renderwall->y;
	renderwall->lastty = -1;
	renderwall->i = 0;
	while (renderwall->i < renderwall->wallheight)
	{
		renderwall->ty = (renderwall->i / (float)renderwall->wallheight)
			* renderwall->texture->height;
		if (renderwall->lastty != renderwall->ty)
		{
			renderwall->color = getpixel(renderwall->texture,
					renderwall->texturecol, renderwall->ty);
			renderwall->color = darken_color(renderwall->color,
					renderwall->brightness);
			renderwall->lastty = renderwall->ty;
		}
		drawpixel(cub->framebuff, screencol, renderwall->y + renderwall->i,
			renderwall->color);
		renderwall->i++;
	}
}

void	renderwall(t_cub *cub, int screencol, t_rayresult *ray)
{
	t_renderwall	renderwall;

	renderwall.brightness = 0;
	renderwall.dist = cos(toradian(ray->rayangle - cub->pyaw))
		* distance(cub->ploc, ray->hit);
	renderwall.sizeper = 1 / renderwall.dist + 0.0001f;
	if (renderwall.sizeper <= 0)
		return ;
	renderwall.ysize = cub->win_res.y * renderwall.sizeper;
	renderwall.y = cub->win_res.y / 2 - renderwall.ysize / 2;
	renderwall.yend = cub->win_res.y / 2 + renderwall.ysize / 2;
	faces(ray, &renderwall, cub);
	drawwall(cub, &renderwall, screencol);
}
