NAME = cub3d

CC = cc

SRC = main.c\
	parsing/map_init.c\
	parsing/validate_map.c\
	parsing/validate_walls.c\
	parsing/validate_textures.c\
	parsing/utils.c\
	parsing/errors.c\
	parsing/parse_cub1.c\
	gnl/get_next_line.c\
	gnl/get_next_line_utils.c\
	execution/exec.c\
	execution/key_handle.c\
	execution/ray_init.c\
	execution/minimap_tools.c\
	execution/minimap_v2.c\
	execution/minimap.c\
	execution/cast_ray.c\
	helper_main/free.c\
	helper_main/utils.c\
	helper_main/init_textures.c\
	helper_main/init_walls.c\

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g3

XFLAGS = -lXext -lX11 -lm -lmlx

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ)  -L libft -lft  -o $(NAME) $(XFLAGS)

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SCONDARY: $(OBJ)

