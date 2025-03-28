NAME        = so_long
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I./mlx

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    MLX_FLAGS = -L./mlx -lmlx -framework OpenGL -framework AppKit
else
    MLX_FLAGS = -L ./mlx -lmlx -lXext -lX11 -lm -lz
endif


SRCS        = so_long.c \
			map_parse.c \
			map_functs.c \
			inc/gnl/get_next_line.c \
       		inc/gnl/get_next_line_utils.c \
			map_control.c \
			reach_map.c \
			draw.c \
			moves.c \
			end.c

all: $(NAME)

$(NAME): $(SRCS) $(MLX)
	$(CC) $(CFLAGS) $(SRCS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re