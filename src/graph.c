/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:21 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/13 13:32:10 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int loop(t_cub *cub)
{
	moverot(cub);
	renderframe(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->window, cub->framebuff->img, 0, 0);
	cub->t++;
	return (0);
}

void initgraph(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	// if (!sl->mlx_ptr)
	//	close_window(sl, 1);
	cub->window = mlx_new_window(cub->mlx_ptr, cub->win_res.x, cub->win_res.y,
								 "Klum3D");
	cub->img_n = loadimg(cub, "textures/blackstone.xpm");
	cub->img_s = loadimg(cub, "textures/crimson_nylium.xpm");
	cub->img_w = loadimg(cub, "textures/resin_bricks.xpm");
	cub->img_e = loadimg(cub, "textures/tnt_side.xpm");
	printf("x %d y %d\n", cub->win_res.x, cub->win_res.y);
	cub->framebuff = newimg(cub, cub->win_res.x, cub->win_res.y);
	listeninputs(cub);
	mlx_loop_hook(cub->mlx_ptr, loop, cub);
	mlx_loop(cub->mlx_ptr);
}
