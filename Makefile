NAME = cub3d

CC = cc

SRC = main.c\
   map_init.c\
   validate_map.c\
   validate_walls.c\
   validate_textures.c\
   gnl/get_next_line.c\
   gnl/get_next_line_utils.c\

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

XFLAGS = -lXext -lX11 -lm -lmlx

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ)  -L libft -lft -o $(NAME) $(XFLAGS)

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SCONDARY: $(OBJ)

