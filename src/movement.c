/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:05:00 by max               #+#    #+#             */
/*   Updated: 2025/05/04 16:41:33 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#define MOVESPEED 0.015
#define ROTSPEED 0.7

void moverot(t_cub *cub)
{
	t_vec2f vdir;
	t_vec2f newloc;

	if (cub->movement.x != 0 || cub->movement.y != 0)
	{
		cub->lastploc.x = cub->ploc.x;
		cub->lastploc.y = cub->ploc.y;
		vdir = yawtovec(cub->pyaw + vectoyaw(cub->movement));
		vdir.x *= MOVESPEED;
		vdir.y *= MOVESPEED;
		newloc.x = cub->ploc.x + vdir.x;
		newloc.y = cub->ploc.y + vdir.y;
		if (!(newloc.x >= 0 && newloc.x < cub->mwidth && newloc.y >= 0 && newloc.y < cub->mheight && cub->map[(int) (cub->ploc.y + vdir.y * 15)][(int) (cub->ploc.x + vdir.x * 15)] == WALL))
			cub->ploc = newloc;
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
	} else
		return ;
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
		printf("Esc exit!\n");
		closewindow(cub);
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

void listeninputs(t_cub *cub)
{
    mlx_hook(cub->window, KeyPress, KeyPressMask, &handle_keypress, cub);
	mlx_hook(cub->window, KeyRelease, KeyReleaseMask, &handle_keyrelease, cub);
}
