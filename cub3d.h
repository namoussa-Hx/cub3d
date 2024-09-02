/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:56:58 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/02 23:33:59 by elchakir         ###   ########.fr       */
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
#include  <mlx.h>
#include <sys/time.h>
# define WIDTH 1920
# define HEIGHT 1080
# define		PI 3.14159265359
//# define		move_speed 5.0
//# define		rotation_speed 0.1

typedef struct s_player
{
	// double		x;
	// double		y;
	// double		dir_x;
	// double		dir_y;
	double		angle;
	double		fov;
	double		player_x;
	double		player_y;
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
	int			width;
}	t_map;

typedef struct s_vec
{
	int  x;
	int  y;
	int map_x;
	int map_y;
	int step_x;
	int step_y;
	double side_dist_x;
	double side_dist_y;
	double ray_dir_x;
	double ray_dir_y;
	int hit;
	int side;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
}	t_vec;
typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		maze;
	t_player	player;
	t_vec		vector;
	void        *img;
	char        *img_data;
	int         bpp;
	int         size_line;
    	int         endian;
    	double      oldTime;
	double      currentTime;
	double		frame_Time;
	double		move_speed;
	double      rot_speed;

}				t_data;

int update(t_data *data);
void render_flor(t_data *game);
void render_color(t_data *game) ;
void render_3d_projection(t_data *game, float distance, int ray_index, int tile_size) ;
void cast_ray_dda(t_data *game, float angle, int ray_index, int tile_size);
int key_hook(int keycode, t_data *game) ;
int				check_is_map_valid(t_data *prog, char *file);
int				validate_walls(t_map *maze);
int				check_empty(t_map *maze);
int				print_error(char *str);
int				map_copy(t_map *prog, char *file);
int				check_textures(t_data *prog);
int				my_strchr(char *str, char *c);
int				check_extension(char *file);
int				free_line(char *line);
int				check_conditions(char ch, int count);
int				parse_cub(char *file, t_data *prog);
int				is_skip(char *line, int flag);
int				should_skip(char *line);
int				check_valid_char(char c, int flag);
void			draw_map(t_data *game, int tile_size);

#endif
