/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:56:58 by namoussa          #+#    #+#             */
/*   Updated: 2024/08/28 23:57:00 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
// #include <mlx.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		player_x;
	double		player_y;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct s_map
{
	char		**map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			f;
	int			c;
	int			height;
}				t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		maze;
	t_player	player;
}				t_data;

int				check_is_map_valid(t_data *prog, char *file);
int				validate_walls(t_map *maze);
int				check_empty(t_map *maze);
int				print_error(char *str);
int				map_copy(t_map *prog, char *file);
int				check_textures(t_data *prog);
int				my_strchr(char *str, char *c);
int				check_extension(char *file);
int				check_conditions(char ch, int count);
int				parse_cub(char *file, t_data *prog);
int				check_valid_char(char c, int flag);

#endif
