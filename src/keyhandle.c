/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:14:57 by mrotceig          #+#    #+#             */
/*   Updated: 2025/05/06 15:23:50 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	wtfnorm(float **ptr, float *val, float *ptrval, float value)
{
	*ptr = ptrval;
	*val = value;
}

/**
 * Z = 119
 * S = 115
 * D = 100
 * Q = 97
 */
void	keyhandle(t_cub *cub, int keycode, bool value)
{
	float	*ptr;
	float	val;

	if (keycode == 119)
		wtfnorm(&ptr, &val, &cub->movement.y, -1);
	else if (keycode == 115)
		wtfnorm(&ptr, &val, &cub->movement.y, 1);
	else if (keycode == 100)
		wtfnorm(&ptr, &val, &cub->movement.x, 1);
	else if (keycode == 97)
		wtfnorm(&ptr, &val, &cub->movement.x, -1);
	else if (keycode == 65363)
		wtfnorm(&ptr, &val, &cub->rotation, 1);
	else if (keycode == 65361)
		wtfnorm(&ptr, &val, &cub->rotation, -1);
	else
		return ;
	if (value)
		*ptr = val;
	else if (*ptr == val)
		*ptr = 0;
}
