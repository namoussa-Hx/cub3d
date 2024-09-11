""int update(t_data *game)
{
    int x = 0;
    int tile_size = 30;
    float ray_angle;
    static int index;
    int *player;

    if (index >= SPRITE_FRAMES * 3)
		index = 0;
	player = game->walls->addr_player[index / 3];

    memset(game->img_data, 0, WIDTH * HEIGHT * (game->bpp / 8));

    render_color(game);
    render_flor(game);
    while (x < WIDTH)
    {
        ray_angle = game->player.angle + atanf((x - WIDTH / 2.0) / (WIDTH / 2.0 / tanf(game->player.fov / 2.0)));
        cast_ray_dda(game, ray_angle, x, tile_size);
        x++;
    }
    render_minimap(game);
    render1_player(game, &player);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    index++;
    return 0;
}" "void render1_player(t_data *game, int **player)
{
    int i;
    int  j;
    int src_index;
    int x_start;
    int y_start;
    unsigned int *texture_addr;
    unsigned int *img_addr;

    texture_addr = (unsigned int *)player;
    img_addr = (unsigned int *)game->img_data;

    x_start = 0;
    y_start = 0;

    if (x_start < 0) x_start = 0;
    if (y_start < 0) y_start = 0;
    float x_scale = (float)texture_addr / (WIDTH );
    float y_scale = (float) texture_addr/ (HEIGHT);
    
    i = 0;
    while (i < HEIGHT)
    {
        j = 0;
        while (j < WIDTH)
        {

           
            src_index = (int)(j * x_scale) + (int)(i * y_scale) * texture_addr;
            if (x_start + j >= 0 && x_start + j < (WIDTH) && y_start + i >= 0 && y_start + i < HEIGHT)
            {
                if (texture_addr[src_index] != 0xff000000)
                    img_addr[x_start + j + y_start + i * WIDTH] = texture_addr[src_index];
            }
            j++;
        }
        i++;
    }
} " " cc -Wall -Wextra -Werror -fsanitize=address -g3   -c -o main.o main.c
cc -Wall -Wextra -Werror -fsanitize=address -g3   -c -o execution/exec.o execution/exec.c
execution/exec.c:174:28: error: pointer cannot be cast to type 'float'
    float x_scale = (float)texture_addr / (WIDTH );
                           ^~~~~~~~~~~~
execution/exec.c:175:29: error: pointer cannot be cast to type 'float'
    float y_scale = (float) texture_addr/ (HEIGHT);
                            ^~~~~~~~~~~~
execution/exec.c:185:65: error: invalid operands to binary expression ('int' and 'unsigned int *')
            src_index = (int)(j * x_scale) + (int)(i * y_scale) * texture_addr;
                                             ~~~~~~~~~~~~~~~~~~ ^ ~~~~~~~~~~~~
3 errors generated.
make: *** [<builtin>: execution/exec.o] Error 1
""