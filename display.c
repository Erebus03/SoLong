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

#define UP 65362
#define DOWN 65364
#define RIGHT 65363
#define LEFT 65361
#define CLOSE 65307

int	key_input(int key, t_game *game)
{
	if (key == UP)
		move_up(game, game->p_pos[0], game->p_pos[1]);
	if (key == DOWN)
		move_down(game, game->p_pos[0], game->p_pos[1]);
	if (key == RIGHT)
		move_right(game, game->p_pos[0], game->p_pos[1]);
	if (key == LEFT)
		move_left(game, game->p_pos[0], game->p_pos[1]);
	if (key == CLOSE)
		cleanup(game, 0);
	return (0);
}

int	put_image(t_game *g, char cell, int x, int y)
{
	if (!g->mlx || !g->win || !g->imgs->wall)
		return (0);
	usleep(290);//		change it based on where your executing it
	if (cell == '0')
		return (mlx_put_image_to_window(g->mlx, g->win, g->imgs->floor,
				x * 50, y * 50));
	else if (cell == 'C')
		return (mlx_put_image_to_window(g->mlx, g->win
				, g->imgs->coin[g->frame % 2], x * 50, y * 50));
	else if (cell == 'P')
		return (mlx_put_image_to_window(g->mlx, g->win
				, g->imgs->p_left[g->frame % 2], x * 50, y * 50));
	else if (cell == 'E')
	{
		if (g->coin == 0)
			return (mlx_put_image_to_window(g->mlx, g->win, g->imgs->exit,
					x * 50, y * 50));
		else
			return (mlx_put_image_to_window(g->mlx, g->win, g->imgs->chained,
					x * 50, y * 50));
	}
	else if (cell == 'N')
		return (mlx_put_image_to_window(g->mlx, g->win
				, g->imgs->enemy[g->frame % 2], x * 50, y * 50));
	return (0);
}

int	loop_init(t_game *g)
{
	int (x), (y);
	g->frame++;
	if (g->frame >= 12)
		g->frame = 0;
	y = 0;
	while (y < g->rows)
	{
		x = 0;
		while (x < g->cols)
		{
			// no error check??
			if (g->map[y][x] == '1')
				mlx_put_image_to_window(g->mlx, g->win, g->imgs->wall,
					x * 50, y * 50);
			else
				put_image(g, g->map[y][x], x, y);// figure out frames and that
			x++;
		}
		y++;
	}
	return (1);
}

int	win_init(t_game *game, t_paths **path)
{
	assigne_paths(path);
	if (!assigne_images(game, path))
	{
		ft_printf("Error\nCouldn't assigne images!\n");
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->cols * 50,
			game->rows * 50, "Solong - hahahahah");
	return (1);
}

void	assigne_paths(t_paths **p)
{
	(*p)->wall = "pics/wall.xpm";
	(*p)->floor = "pics/floor.xpm";
	(*p)->exit = "pics/exit.xpm";
	(*p)->chained = "pics/chained.xpm";
	(*p)->enemy[0] = "pics/enemy/1.xpm";
	(*p)->enemy[1] = "pics/enemy/2.xpm";
	(*p)->coin[0] = "pics/sheep/1.xpm";
	(*p)->coin[1] = "pics/sheep/2.xpm";
	(*p)->attack[0] = "pics/attack/1.xpm";
	(*p)->attack[1] = "pics/attack/2.xpm";
	(*p)->attack[2] = "pics/attack/3.xpm";
	(*p)->attack[3] = "pics/attack/4.xpm";
	(*p)->p_up[0] = "pics/monster/right1.xpm";
	(*p)->p_up[1] = "pics/monster/right1.xpm";
	(*p)->p_down[0] = "pics/monster/left1.xpm";
	(*p)->p_down[1] = "pics/monster/left1.xpm";
	(*p)->p_right[0] = "pics/monster/right1.xpm";
	(*p)->p_right[1] = "pics/monster/right2.xpm";
	(*p)->p_left[0] = "pics/monster/left1.xpm";
	(*p)->p_left[1] = "pics/monster/left2.xpm";
}
