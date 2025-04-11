/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:14 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/11 21:24:33 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	toradian(float degrees)
{
	return (degrees * (M_PI / 180.0));
}

t_vec2f	yawtovec(float yaw)
{
	t_vec2f	v;

	yaw = fmod(fmod(yaw, 360.0f) + 360.0f, 360.0f);
	v.x = cos(toradian(yaw));
	v.y = sin(toradian(yaw));
	return (v);
}

float	distance(t_vec2f first, t_vec2f second)
{
	float	dx;
	float	dy;

	dx = second.x - first.x;
	dy = second.y - first.y;
	return (sqrt(dx * dx + dy * dy));
}
