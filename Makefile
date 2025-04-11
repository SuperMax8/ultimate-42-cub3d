NAME		=	so_long
MLX_DIR		=	mlx
MLX_LIB		=	$(MLX_DIR)/libmlx.a

INCLUDES	=	-I/usr/include -Imlx

RM			=	rm -rf
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	solong.c \
				solong2.c \
				graphic1.c \
				get_next_line.c \
				renderer.c \
				map.c \
				pathfind.c \
				get_next_line_utils.c \
				ft_printf.c \
				ft_printf_utils.c

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
