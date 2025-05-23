/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrotceig <mrotceig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:50:46 by mrotceig          #+#    #+#             */
/*   Updated: 2025/05/12 16:26:24 by mrotceig         ###   ########.fr       */
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
	int			x;
	int			y;
}				t_vec2;

typedef struct vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct s_imgdata
{
	void		*img;
	int			width;
	int			height;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_rayresult
{
	t_vec2f		hit;
	char		face;
	float		rayangle;
}				t_rayresult;

typedef struct s_map
{
	char		**file;
	char		**map;
	char		**mapcopy;
	char		*texturenorth;
	char		*texturesouth;
	char		*textureeast;
	char		*texturewest;
	char		*ptrtexture;
	int			*rgb;
	int			checkplayer;
	int			color;
	int			countcolor;
	int			x;
	int			y;
	int			fd;
	int			count;
	int			sizemap;
	int			isgood;
	int			e;
}				t_map;

typedef struct cub
{
	int			t;
	char		**map;
	int			mwidth;
	int			mheight;
	t_vec2f		movement;
	float		rotation;
	t_vec2f		lastploc;
	t_vec2f		ploc;
	float		pyaw;
	void		*mlx_ptr;
	void		*window;
	t_vec2		win_res;
	t_img		*framebuff;
	int			color_ceiling;
	int			color_floor;
	t_img		*img_n;
	t_img		*img_s;
	t_img		*img_e;
	t_img		*img_w;
	t_map		*mapmap;
}				t_cub;

typedef struct s_raycastwall
{
	int			mapx;
	int			mapy;
	float		delta_distx;
	float		delta_disty;
	int			stepx;
	int			stepy;
	float		side_distx;
	float		side_disty;
	int			side;
	float		distance;
	bool		hit;
	int			i;
	t_rayresult	*result;
}				t_raycastwall;

typedef struct s_renderwall
{
	float		sizeper;
	int			ysize;
	int			y;
	int			yend;
	t_img		*texture;
	float		worldcol;
	float		colper;
	int			texturecol;
	float		dist;
	int			wallheight;
	int			i;
	float		brightness;
	int			lastty;
	int			color;
	int			ty;
}				t_renderwall;

int				ismapvalid(t_map *map, t_cub *cub);
void			parsing(t_map *map);
int				count_line(t_map *map);
int				ft_strlen(char *str);
int				count_line(t_map *map);

void			initgraph(t_cub *cub);
int				closewindow(void *strc);
void			renderframe(t_cub *cub);
t_rayresult		*raycastwall(t_cub *cub, t_vec2f raydir);
void			renderwall(t_cub *cub, int screencol, t_rayresult *ray);

int				create_trgb(int t, int r, int g, int b);
float			lerp(float a, float b, float f);
int				lerp_color(int color1, int color2, float f);
int				darken_color(int color, float factor);

void			drawsqare(t_cub *cub, t_vec2 coord, int size, int color);
void			fillfloor(t_cub *cub, int color);
void			fillcolor(t_cub *cub, int color);
void			fillvgradient(t_cub *cub, int color1, int color2, int *xywh);

t_vec2f			yawtovec(float yaw);
float			vectoyaw(t_vec2f vec);
float			normyaw(float yaw);
float			distance(t_vec2f first, t_vec2f second);

float			clamp(float x, float min, float max);
float			toradian(float degrees);
float			todegrees(float rad);

void			moverot(t_cub *cub);
void			listeninputs(t_cub *cub);
void			keyhandle(t_cub *cub, int keycode, bool value);

t_img			*loadimg(t_cub *cub, char *file);
t_img			*newimg(t_cub *cub, int width, int height);
void			destroyimg(t_cub *cub, t_img *img);
int				getpixel(t_img *img, int x, int y);
void			drawpixel(t_img *img, int x, int y, int color);

char			*ft_strdup(const char *src);
void			freemap(t_map *map);
int				getinfo(t_map *map, t_cub *cub, int i, int d);
int				checkplayerdirection(t_map *map, t_cub *cub, int d, int i);
int				checkvoid(t_map *map, t_cub *cub, int d, int i);
int				ft_doublestrlen(char **str);
int				ft_strlen(char *str);
char			*ft_strdups(char *str);
void			resizemap(t_map *map, t_cub *cub);
int				ft_atoi(const char *str);
int				floodfill(t_map *map, int i, int d);
void			checkifvisited(t_map *map);
int				mapcopy(t_map *map);
int				checkmap(t_map *map, t_cub *cub);
void			freemapcopy(t_map *map);
int				color(t_map *map, t_cub *cub, int i, int d);
int				copy(t_map *map, int i, int d);
int				triplelen(char **str);

#endif