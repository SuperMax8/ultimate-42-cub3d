/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:47:14 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/13 14:36:45 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	normyaw(float yaw)
{
	return (fmod(fmod(yaw, 360.0f) + 360.0f, 360.0f));
}

t_vec2f	yawtovec(float yaw)
{
	t_vec2f	v;

	yaw = normyaw(yaw - 90.0f);
	v.x = cos(toradian(yaw));
	v.y = sin(toradian(yaw));
	return (v);
}

float vectoyaw(t_vec2f vec)
{
	return normyaw(todegrees(atan2(vec.y, vec.x)) + 90.0f);
}

float	distance(t_vec2f first, t_vec2f second)
{
	float	dx;
	float	dy;

	dx = second.x - first.x;
	dy = second.y - first.y;
	return (sqrt(dx * dx + dy * dy));
}
