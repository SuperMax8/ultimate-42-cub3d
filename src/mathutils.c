/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:38:39 by max               #+#    #+#             */
/*   Updated: 2025/04/13 14:42:37 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	toradian(float degrees)
{
	return (degrees * (M_PI / 180.0));
}

float	todegrees(float rad)
{
	return (rad * (180.0 / M_PI));
}

float clamp(float x, float min, float max)
{
    if (x < min)
        return (min);
    if (x > max)
        return (max);
    return (x);
}
