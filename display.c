/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:38:26 by araji             #+#    #+#             */
/*   Updated: 2025/02/06 13:38:26 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361
# define CLOSE 65307

int	key_input(int key, void *g)// can't i just declare it t_game_info ?
{
	t_game_info *game;

	game = (t_game_info *)g;
	if (key == UP)
		move_up(game, game->var->p_pos[0], game->var->p_pos[1]);
	if (key == DOWN)
		move_down(game, game->var->p_pos[0], game->var->p_pos[1]);
	if (key == RIGHT)
		move_right(game, game->var->p_pos[0], game->var->p_pos[1]);
	if (key == LEFT)
		move_left(game, game->var->p_pos[0], game->var->p_pos[1]);

	if (key == CLOSE)
	{
		// cleanup(game); // segfaults
		mlx_destroy_window(game->mlx, game->win);
		exit (0);
	}
    return (0);
}

int	put_image(t_game_info *g, char cell, int x, int y)
{
	int	ret;

	
	if (!g->mlx || !g->win || !g->imgs->wall)
		return (0);
	ret = 1;

	if (cell == '0')
		ret = mlx_put_image_to_window(g->mlx, g->win, g->imgs->floor,
			x * TILE, y * TILE);
	if (cell == '1')
		ret = mlx_put_image_to_window(g->mlx, g->win, g->imgs->wall,
				x * TILE, y * TILE);
	else if (cell == 'C')
		ret = mlx_put_image_to_window(g->mlx, g->win, g->imgs->coin[0],
				x * TILE, y * TILE);
	else if (cell == 'P')
		ret = mlx_put_image_to_window(g->mlx, g->win, g->imgs->p_left[0],
				x * TILE, y * TILE);
	else if (cell == 'E')
		ret = mlx_put_image_to_window(g->mlx, g->win, g->imgs->exit,
				x * TILE, y * TILE);
	else if (cell == 'N')
		ret = mlx_put_image_to_window(g->mlx, g->win, g->imgs->attack[g->frame],
				x * TILE, y * TILE);
	return (ret);
}

int	loop_init(t_game_info *game)
{
	int	x;
	int	y;
	
	game->frame++;
	if (game->frame > 3)
		game->frame = 0;

	y = 0;
	while (y < game->grid->rows)
	{
		x = 0;
		while (x < game->grid->cols)
		{
			put_image(game, game->map[y][x], x , y);// figure out frames and that
			x++;
		}
		y++;
	}
	return (1);
}

int	win_init(t_game_info *game, t_paths **path)
{
	assigne_paths(path);
	if (!assigne_images(&game->imgs, game->mlx, path))
	{
		ft_printf("Error\nCouldn't assigne images!\n");
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->grid->cols * TILE,
			game->grid->rows * TILE, "Soolowng");
	return (1);
}

void	assigne_paths(t_paths **p)
{
	(*p)->wall = "pics/wall.xpm";
	(*p)->floor = "pics/floor.xpm";
	(*p)->exit = "pics/wall.xpm";
	(*p)->enemy[0] = "pics/enemy/enemy1.xpm";
	(*p)->enemy[1] = "pics/enemy/enemy2.xpm";
	(*p)->coin[0] = "pics/sheep/sheep1.xpm";
	(*p)->coin[1] = "pics/sheep/sheep1.xpm";
	(*p)->attack[0] = "pics/attack/attack1.xpm";
	(*p)->attack[1] = "pics/attack/attack2.xpm";
	(*p)->attack[2] = "pics/attack/attack3.xpm";
	(*p)->attack[3] = "pics/attack/attack4.xpm";
	(*p)->p_up[0] = "pics/monster/monster1.xpm";
	(*p)->p_up[1] = "pics/monster/monster1.xpm";
	(*p)->p_down[0] = "pics/monster/monster1.xpm";
	(*p)->p_down[1] = "pics/monster/monster1.xpm";
	(*p)->p_right[0] = "pics/monster/monster1.xpm";
	(*p)->p_right[1] = "pics/monster/monster1.xpm";
	(*p)->p_left[0] = "pics/monster/dragon.xpm";
	(*p)->p_left[1] = "pics/monster/monster1.xpm";
}
