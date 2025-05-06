NAME		=	cub3D
MLX_DIR		=	mlx
MLX_LIB		=	$(MLX_DIR)/libmlx.a

INCLUDES	=	-I/usr/include -Imlx

RM			=	rm -rf
CC			=	cc
CFLAGS		=	-O3 -march=native -Wall -Wextra -Werror

SRCS		=	src/cub3d.c src/renderer.c src/raycastwall.c src/renderwall.c src/vecutils.c src/colorutils.c src/drawutils.c src/graph.c src/imgutils.c src/movement.c src/keyhandle.c src/mathutils.c src/parsing.c src/get_next_line.c src/get_next_line_utils.c src/chemin.c src/checkfile.c src/checkfloodfill.c src/checkmap.c src/checkmaptoo.c src/color.c src/libft.c

OBJS        = $(SRCS:.c=.o)

MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -lm

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
