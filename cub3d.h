/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:56:58 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/11 00:12:57 by elchakir         ###   ########.fr       */
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

# define WIDTH 1200
# define HEIGHT 900
# define PI 3.14159265359
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define MOVE_SPEED 3.0
# define ROT_SPEED 0.1
# define MINIMAP_RADIUS 100
# define MINIMAP_DIAMETER 200
# define TILE_SIZE 10
# define PLAYER_MARKER_SIZE 4
# define SPRITE_FRAMES 37

# define DOOR1 "textures/door/doors_1.xpm"
# define DOOR2 "textures/door/doors_2.xpm"

typedef struct s_textures
{
	void			*images[16];
	int				*addr[16];
	int				*scale_enemy[16];
	int				bpp[16];
	int				size_line[16];
	int				endian[16];
	int				width[16];
	int				height[16];
}					t_textures;

typedef struct s_free
{
	void			*addr;
	struct s_free	*next;

}					t_free;

extern t_free		*g_free;
typedef struct s_enemy
{
	int				enemy_index;
	int				x;
	int				y;
	int				x_enemy;
	int				y_enemy;
}					t_enemy;
typedef struct s_player
{
	int				x;
	int				y;
	float			angle;
	double			fov;
	double			player_x;
	double			player_y;
}					t_player;

typedef struct s_map
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f;
	int				c;
	int				height;
	int				width;
}					t_map;

typedef struct s_vec
{
	int				x;
	int				y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				hit;
	int				side;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
}					t_vec;

typedef struct s_images
{
	void			*images[7];
	int				*addr[7];
	int				*scale[7];
	int				width[7];
	int				height[7];
	int				bpp[7];
	int				size_line[7];
	int				endian[7];
	void			**player;
	int				**addr_player;
	int				*width_player;
	int				*height_player;
	int				*bpp_player;
	int				*size_line_player;
	int				*endian_player;
}					t_images;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_images		*walls;
	t_map			maze;
	t_player		player;
	t_vec			vector;
	t_enemy			enemy;
	t_textures		*textures;
	void			*image_door;
	int				*addr_door;
	int				*scale_door;
	void			*img;
	char			*img_data;
	int				is_door;
	int				width_door;
	int				height_door;
	int				bpp_door;
	int				size_line_door;
	int				endian_door;
	float			distance_to_door;
	int				is_door_open;
	int				bpp;
	int				size_line;
	int				endian;
	int				hide_mouse;
	int				player_face;
	int				x_mouse_prev;
	int				x_door;
	int				y_door;
}					t_data;

int					update(t_data *data);
void				render1_player(t_data *game, int *player, int texture_width,
						int texture_height);
void				render_flor(t_data *game);
void				render_color(t_data *game);
void				render_3d_projection(t_data *game, float distance,
						int ray_index, int tile_size);
void				cast_ray_dda(t_data *game, float angle, int ray_index,
						int tile_size);
int					key_hook(int keycode, t_data *game);
int					check_is_map_valid(t_data *prog, char *file);
int					validate_walls(t_map *maze);
int					check_empty(t_map *maze);
int					print_error(char *str);
int					map_copy(t_map *prog, char *file);
int					check_textures(t_data *prog);
int					my_strchr(char *str, char *c);
int					check_extension(char *file);
int					check_conditions(char ch, int count);
int					parse_cub(char *file, t_data *prog);
int					is_skip(char *line, int flag);
int					destroy_all(t_data *game);
int					should_skip(char *line);
int					check_valid_char(char c, int flag);
int					render_minimap(t_data *game);
void				init_walls(t_data *game);
void				init_player(t_data *game);
t_free				*newnode(void *address);
void				free_all(t_free **lst);
int					should_skip(char *line);
int					is_comma(char *line);
void				ft_player_angle(t_data *data, char c);
void				*file_to_img(t_data *data, char *img_path, int *w, int *h);
int					is_inside_circle(int x, int y, int center_x, int center_y,
						int radius);
void				addback(t_free **lst, t_free *new);

#endif
