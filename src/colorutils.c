/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:33:35 by mrotceig          #+#    #+#             */
/*   Updated: 2025/05/06 15:40:05 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float	lerp(float a, float b, float f)
{
	return (a + f * (b - a));
}

int	lerp_color(int color1, int color2, float f)
{
	int	t;
	int	r;
	int	g;
	int	b;
	int	colors[8];

	colors[0] = (color1 >> 24) & 0xFF;
	colors[1] = (color1 >> 16) & 0xFF;
	colors[2] = (color1 >> 8) & 0xFF;
	colors[3] = (color1) & 0xFF;
	colors[4] = (color2 >> 24) & 0xFF;
	colors[5] = (color2 >> 16) & 0xFF;
	colors[6] = (color2 >> 8) & 0xFF;
	colors[7] = (color2) & 0xFF;
	t = (int)lerp((float)colors[0], (float)colors[4], f);
	r = (int)lerp((float)colors[1], (float)colors[5], f);
	g = (int)lerp((float)colors[2], (float)colors[6], f);
	b = (int)lerp((float)colors[3], (float)colors[7], f);
	return (create_trgb(t, r, g, b));
}

int	darken_color(int color, float factor)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (factor < 0.0f)
		factor = 0.0f;
	if (factor > 1.0f)
		factor = 1.0f;
	t = (color >> 24) & 0xFF;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * factor);
	g = (int)(g * factor);
	b = (int)(b * factor);
	return (create_trgb(t, r, g, b));
}
