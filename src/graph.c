/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:21 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/11 18:58:23 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	move(t_cub *cub, float dir)
{
	t_vec2f	vdir;

	vdir = yawtovec(cub->pyaw);
	cub->ploc.x += vdir.x * dir;
	cub->ploc.y += vdir.y * dir;
}

static void	rotate(t_cub *cub, float delta)
{
	cub->pyaw += delta;
	cub->pyaw = fmod(fmod(cub->pyaw, 360.0f) + 360.0f, 360.0f);
}

/**
 * Z = 119
 * S = 115
 * D = 100
 * Q = 97
 */
static void	keyhandle(t_cub *cub, int keycode, bool value)
{
	if (keycode == 119)
		cub->forwardpress = value;
	else if (keycode == 115)
		cub->backwardpress = value;
	else if (keycode == 100)
		cub->rightpress = value;
	else if (keycode == 97)
		cub->leftpress = value;
}

static int	handle_keypress(int keycode, t_cub *cub)
{
	if (keycode == 65307)
	{
		// close_window(sl, 0);
		printf("End !");
		exit(0);
	}
	else
		keyhandle(cub, keycode, true);
	return (0);
}

static int	handle_keyrelease(int keycode, t_cub *cub)
{
	keyhandle(cub, keycode, false);
	return (0);
}

static int	computemove(t_cub *cub)
{
	if (cub->forwardpress)
		move(cub, 0.01);
	else if (cub->backwardpress)
		move(cub, -0.01);
	else if (cub->rightpress)
		rotate(cub, 0.1);
	else if (cub->leftpress)
		rotate(cub, -0.1);
	return (0);
}

int	loop(t_cub *cub)
{
	computemove(cub);
	renderframe(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->window, cub->framebuff.img, 0,
		0);
	cub->t++;
    printf("xpos: %f  ypos: %f  yaw: %f\n", cub->ploc.x, cub->ploc.y,
		cub->pyaw);
	return (0);
}

void	initgraph(t_cub *cub)
{
	int	img_width;
	int	img_height;

	cub->mlx_ptr = mlx_init();
	// if (!sl->mlx_ptr)
	//	close_window(sl, 1);
	cub->window = mlx_new_window(cub->mlx_ptr, cub->win_res.x, cub->win_res.y,
			"KKlum!");
	printf("x %d y %d\n", cub->win_res.x, cub->win_res.y);
	cub->framebuff.img = mlx_new_image(cub->mlx_ptr, cub->win_res.x,
			cub->win_res.y);
	cub->framebuff.addr = mlx_get_data_addr(cub->framebuff.img,
			&cub->framebuff.bits_per_pixel, &cub->framebuff.line_length,
			&cub->framebuff.endian);
	mlx_hook(cub->window, KeyPress, KeyPressMask, &handle_keypress, cub);
	mlx_hook(cub->window, KeyRelease, KeyReleaseMask, &handle_keyrelease, cub);
	mlx_loop_hook(cub->mlx_ptr, loop, cub);
	mlx_loop(cub->mlx_ptr);
}
