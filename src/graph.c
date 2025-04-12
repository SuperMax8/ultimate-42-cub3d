/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:21 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/12 03:55:51 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#define MOVESPEED 0.02
#define ROTSPEED 1.5

static void moverot(t_cub *cub)
{
	t_vec2f vdir;

	if (cub->movement.x != 0 || cub->movement.y != 0)
	{
		cub->lastploc.x = cub->ploc.x;
		cub->lastploc.y = cub->ploc.y;
		vdir = yawtovec(cub->pyaw + vectoyaw(cub->movement));
		cub->ploc.x += vdir.x * MOVESPEED;
		cub->ploc.y += vdir.y * MOVESPEED;
	}

	cub->pyaw += cub->rotation * ROTSPEED;
	cub->pyaw = normyaw(cub->pyaw);
}

/**
 * Z = 119
 * S = 115
 * D = 100
 * Q = 97
 */
static void keyhandle(t_cub *cub, int keycode, bool value)
{
	float *ptr;
	float val;

	if (keycode == 119)
	{
		ptr = &cub->movement.y;
		val = -1;
	}
	else if (keycode == 115)
	{
		ptr = &cub->movement.y;
		val = 1;
	}
	else if (keycode == 100)
	{
		ptr = &cub->movement.x;
		val = 1;
	}
	else if (keycode == 97)
	{
		ptr = &cub->movement.x;
		val = -1;
	}
	else if (keycode == 65363)
	{
		ptr = &cub->rotation;
		val = 1;
	}
	else if (keycode == 65361)
	{
		ptr = &cub->rotation;
		val = -1;
	}
	if (value)
		*ptr = val;
	else if (*ptr == val)
		*ptr = 0;
	//printf("keycode: %d\n", keycode);
}

static int handle_keypress(int keycode, t_cub *cub)
{
	if (keycode == 65307)
	{
		// close_window(sl, 0);
		printf("End !\n");
		exit(0);
	}
	else
		keyhandle(cub, keycode, true);
	return (0);
}

static int handle_keyrelease(int keycode, t_cub *cub)
{
	keyhandle(cub, keycode, false);
	return (0);
}

int loop(t_cub *cub)
{
	moverot(cub);
	renderframe(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->window, cub->framebuff.img, 0,
							0);
	cub->t++;
	return (0);
}

void initgraph(t_cub *cub)
{
	int img_width;
	int img_height;

	cub->mlx_ptr = mlx_init();
	// if (!sl->mlx_ptr)
	//	close_window(sl, 1);
	cub->window = mlx_new_window(cub->mlx_ptr, cub->win_res.x, cub->win_res.y,
								 "Klum3D");
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
