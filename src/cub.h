/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:14:37 by mrotceig          #+#    #+#             */
/*   Updated: 2025/04/11 15:42:56 by mrotceig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

typedef struct vec2f
{
	float	x;
	float	y;
}			t_vec2f;

typedef struct cub
{
	t_vec2f	ploc;
	t_vec2f	pdir;
	void	*mlx_ptr;
	void	*window;
	int		color_ceiling;
	int		color_floor;
	void	*img_n;
	void	*img_s;
	void	*img_e;
	void	*img_w;
}			t_cub;

#endif