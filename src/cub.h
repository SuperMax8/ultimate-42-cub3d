/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:38:57 by max               #+#    #+#             */
/*   Updated: 2025/04/13 14:39:00 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../mlx/mlx.h"
# include <X11/X.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define EAST 'E'
# define NORTH 'N'
# define WEST 'W'
# define SOUTH 'S'
# define WALL '1'
# define VOID '0'

typedef struct vec2
{
	int		x;
	int		y;
}			t_vec2;

typedef struct vec2f
{
	float	x;
	float	y;
}			t_vec2f;

typedef struct s_imgdata
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_rayresult
{
	t_vec2f	hit;
	char	face;
	float	rayangle;
}			t_rayresult;

typedef struct cub
{
	int		t;
	char	**map;
	int		mwidth;
	int		mheight;
	t_vec2f	movement;
	float	rotation;
	t_vec2f	lastploc;
	t_vec2f	ploc;
	float	pyaw;
	void	*mlx_ptr;
	void	*window;
	t_vec2	win_res;
	t_img	*framebuff;
	int		color_ceiling;
	int		color_floor;
	t_img	*img_n;
	t_img	*img_s;
	t_img	*img_e;
	t_img	*img_w;
}			t_cub;

typedef struct s_map
{
	char	**file;
	char	**map;
	char	*texturenorth;
	char	*texturesouth;
	char	*textureeast;
	char	*texturewest;
	char	*ptrtexture;
	int		x;
	int		y;
	int		fd;
	int		count;
}			t_map;

int			ismapvalid(t_map *map, t_cub *cub);
void		parsing(t_map *map);
int			count_line(t_map *map);
int			ft_strlen(char *str);
int			count_line(t_map *map);

void		initgraph(t_cub *cub);
void		closewindow(t_cub *cub);
void		renderframe(t_cub *cub);

t_vec2f		yawtovec(float yaw);
float		vectoyaw(t_vec2f vec);
float		normyaw(float yaw);
float		distance(t_vec2f first, t_vec2f second);

float		clamp(float x, float min, float max);
float		toradian(float degrees);
float		todegrees(float rad);

void		moverot(t_cub *cub);
void		listeninputs(t_cub *cub);

t_img		*loadimg(t_cub *cub, char *file);
t_img		*newimg(t_cub *cub, int width, int height);
void		destroyimg(t_cub *cub, t_img *img);
int			getpixel(t_img *img, int x, int y);
void		drawpixel(t_img *img, int x, int y, int color);

#endif