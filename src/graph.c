/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:21 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/13 14:27:17 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void closewindow(t_cub *cub)
{
	destroyimg(cub, cub->framebuff);
	destroyimg(cub, cub->img_n);
	destroyimg(cub, cub->img_s);
	destroyimg(cub, cub->img_w);
	destroyimg(cub, cub->img_e);
	if (cub->window)
		mlx_destroy_window(cub->mlx_ptr, cub->window);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	free(cub->map);
	printf("Clean exit!\n");
	exit(0);
}

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
	if (!cub->mlx_ptr)
		closewindow(cub);
	cub->window = mlx_new_window(cub->mlx_ptr, cub->win_res.x, cub->win_res.y,
								 "Klum3D");
	cub->img_n = loadimg(cub, "textures/blackstone.xpm");
	cub->img_s = loadimg(cub, "textures/crimson_nylium.xpm");
	cub->img_w = loadimg(cub, "textures/resin_bricks.xpm");
	cub->img_e = loadimg(cub, "textures/tnt_side.xpm");
	cub->framebuff = newimg(cub, cub->win_res.x, cub->win_res.y);
	if (!cub->window || !cub->img_n || !cub->img_s || !cub->img_w || !cub->img_e || !cub->framebuff)
		closewindow(cub);
	printf("x %d y %d\n", cub->win_res.x, cub->win_res.y);
	listeninputs(cub);
	mlx_loop_hook(cub->mlx_ptr, loop, cub);
	mlx_loop(cub->mlx_ptr);
}
