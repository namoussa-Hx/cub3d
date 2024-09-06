

    if (game->player.angle >= 2 * PI)
                    game->player.angle -= 2 * PI;
             if (game->player.angle < 0)
                    game->player.angle += 2 * PI;
            // printf("angle %f\n", game->player.angle);
            if (game->player.angle >= 0 && game->player.angle <= PI / 2)
            {
                printf("111angle %f\n", game->player.angle);
                game->player.angle -= 0.09;
            }
            else if (game->player.angle > PI / 2 && game->player.angle <= PI)
            {
                printf("222angle %f\n", game->player.angle);
                game->player.angle += 0.09;
            }
            else if (game->player.angle > PI && game->player.angle <= 3 * PI / 2)
            {
                printf("333angle %f\n", game->player.angle);
                game->player.angle -= 0.09;
            }
            else if (game->player.angle > 3 * PI / 2 && game->player.angle <= 2 * PI)
            {
                printf("444angle %f\n", game->player.angle);
                game->player.angle += 0.09;
            }
