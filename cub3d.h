/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:56:58 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/08 17:50:02 by elchakir         ###   ########.fr       */
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
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define WIDTH 1800
# define HEIGHT 1000
# define PI 3.14159265359
# define UP 1
# define DOWN 2
# define LEFT 3
# define RIGHT 4
# define MOVE_SPEED 5.0
# define ROT_SPEED 0.1
#define MINIMAP_RADIUS 100
#define MINIMAP_DIAMETER (MINIMAP_RADIUS * 2)
#define TILE_SIZE 10
#define PLAYER_MARKER_SIZE 4

/***************ENEMY*********************/
# define ENEMY0 "textures/frame1_xpm/enemy_0.xpm"
# define ENEMY1 "textures/frame1_xpm/enemy_1.xpm"
# define ENEMY2 "textures/frame1_xpm/enemy_2.xpm"
# define ENEMY3 "textures/frame1_xpm/enemy_3.xpm"
# define ENEMY4 "textures/frame1_xpm/enemy_4.xpm"
# define ENEMY5 "textures/frame1_xpm/enemy_5.xpm"
# define ENEMY6 "textures/frame1_xpm/enemy_6.xpm"
# define ENEMY7 "textures/frame1_xpm/enemy_7.xpm"
# define ENEMY8 "textures/frame1_xpm/enemy_8.xpm"
# define ENEMY9 "textures/frame1_xpm/enemy_9.xpm"
# define ENEMY10 "textures/frame1_xpm/enemy_10.xpm"
# define ENEMY11 "textures/frame1_xpm/enemy_11.xpm"
# define ENEMY12 "textures/frame1_xpm/enemy_12.xpm"
# define ENEMY13 "textures/frame1_xpm/enemy_13.xpm"
# define ENEMY14 "textures/frame1_xpm/enemy_14.xpm"
# define ENEMY15 "textures/frame1_xpm/enemy_15.xpm"
/****************************************/
#define DOOR1 "textures/door/doors_1.xpm"
#define DOOR2 "textures/door/doors_2.xpm"
typedef struct s_textures
{
	void *images[16];
	int *addr[16];
	int *scale_enemy[16];
	int bpp[16];
	int size_line[16];
	int endian[16];
	int width[16];
	int height[16];
}				t_textures;
typedef struct s_enemy
{
	int enemy_index;
	int x;
	int y;
	int x_enemy;
	int y_enemy;
}				t_enemy;
typedef struct s_player
{
	int			x;
	int			y;
	// double		dir_x;
	// double		dir_y;
	float		angle;
	double		fov;
	double		player_x;
	double		player_y;
}				t_player;

// typedef struct s_mini_map
// {
// 	void		*img;
// 	char		*img_data;
// 	int			bpp;
// 	int			size_line;
// 	int			endian;
// }				t_mini_map;

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
}				t_map;

typedef struct s_vec
{
	int			x;
	int			y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		ray_dir_x;
	double		ray_dir_y;
	int			hit;
	int			side;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
}				t_vec;

typedef struct s_images
{
	void		*images[6];
	int			*addr[6];
	int			*scale[6];
	int			width[6];
	int			height[6];
	int			bpp[6];
	int			size_line[6];
	int			endian[6];
}				t_images;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_images	*walls;
	t_map		maze;
	t_player	player;
	t_vec		vector;
	t_enemy		enemy;
	t_textures	*textures;
	// t_mini_map	mini_map;
	void *image_door;
	int *addr_door;
	int *scale_door;
	void		*img;
	char		*img_data;
	int is_door;
	int width_door;
	int height_door;
	int bpp_door;
	int size_line_door;
	int endian_door;
	float distance_to_door;
	int 	is_door_open;
	int			bpp;
	int			size_line;
	int			endian;
	int			hide_mouse;
	int			player_face;
	int			x_mouse_prev;
	int 		x_door;
	int 		y_door;

}				t_data;

int				update(t_data *data);
void			render_flor(t_data *game);
void			render_color(t_data *game);
void			render_3d_projection(t_data *game, float distance,
					int ray_index, int tile_size);
void			cast_ray_dda(t_data *game, float angle, int ray_index,
					int tile_size);
int				key_hook(int keycode, t_data *game);
int				check_is_map_valid(t_data *prog, char *file);
int				validate_walls(t_map *maze);
int				check_empty(t_map *maze);
int				print_error(char *str);
void			init_textures(t_data *game);
void			texture_address(t_data *game);
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
int 			render_minimap(t_data *game);
void			init_walls(t_data *game);
void			*file_to_img(t_data *data, char *img_path, int *w, int *h);
void			render_enemy(t_data *game);
int				is_inside_circle(int x, int y, int center_x, int center_y, int radius);
// void			draw_map(t_data *game, int tile_size);

#endif
