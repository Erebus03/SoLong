/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:56:50 by araji             #+#    #+#             */
/*   Updated: 2025/02/18 13:56:50 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	attack(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->imgs->attack[0], x * 50, y * 50);
	mlx_put_image_to_window(game->mlx, game->win, game->imgs->attack[1], x * 50, y * 50);
	sleep(2);//remove this later
	mlx_put_image_to_window(game->mlx, game->win, game->imgs->attack[2], x * 50, y * 50);
	mlx_put_image_to_window(game->mlx, game->win, game->imgs->attack[3], x * 50, y * 50);

}

int	move_up(t_game *game, int x, int y)
{
	char	next;

	next = game->map[y - 1][x];
	if ((next == 'E' && game->coin == game->collected) || next == 'N')
	{
		if (next == 'N')
			attack(game, x, y - 1);
		game->moves++;
		ft_printf("Moves: %d With (%d/%d) Sheeps Eaten\n", game->moves, game->collected, game->coin);
		cleanup(game, 0);
	}
	if (next != '1' && next != 'E')
	{
		if (next == 'C')
			game->collected++;
		game->map[y - 1][x] = game->map[y][x];
		game->map[y][x] = '0';
		game->p_pos[1] = y - 1;
		game->moves++;
		ft_printf("Moves: %d With (%d/%d) Sheeps Eaten\n", game->moves, game->collected, game->coin);
		return (0);
	}
	return (0);
}

int	move_down(t_game *game, int x, int y)
{
	char	next;

	next = game->map[y + 1][x];
	if ((next == 'E' && game->coin == game->collected) || next == 'N')
	{
		if (next == 'N')
			attack(game, x, y + 1);
		game->moves++;
		ft_printf("Moves: %d With (%d/%d) Sheeps Eaten\n", game->moves, game->collected, game->coin);
		cleanup(game, 0);
	}
	if (next != '1' && next != 'E')
	{
		if (next == 'C')
			game->collected++;
		game->map[y + 1][x] = game->map[y][x];
		game->map[y][x] = '0';
		game->p_pos[1] = y + 1;
		game->moves++;
		ft_printf("Moves: %d With (%d/%d) Sheeps Eaten\n", game->moves, game->collected, game->coin);
		return (0);
	}
	return (0);
}

int	move_right(t_game *game, int x, int y)
{
	char	next;

	next = game->map[y][x + 1];
	game->direction = 1;
	if ((next == 'E' && game->coin == game->collected) || next == 'N')
	{
		if (next == 'N')
			attack(game, x + 1, y);
		game->moves++;
		ft_printf("Moves: %d With (%d/%d) Sheeps Eaten\n", game->moves, game->collected, game->coin);
		cleanup(game, 0);
	}
	if (next != '1' && next != 'E')
	{
		if (next == 'C')
			game->collected++;
		game->map[y][x + 1] = game->map[y][x];
		game->map[y][x] = '0';
		game->p_pos[0] = x + 1;
		game->moves++;
		ft_printf("Moves: %d With (%d/%d) Sheeps Eaten\n", game->moves, game->collected, game->coin);
		return (0);
	}
	return (0);
}

int	move_left(t_game *game, int x, int y)
{
	char	next;

	next = game->map[y][x - 1];
	game->direction = 0;
	if ((next == 'E' && game->coin == game->collected) || next == 'N')
	{
		if (next == 'N')
			attack(game, x - 1, y);
		game->moves++;
		ft_printf("Moves: %d With (%d/%d) Sheeps Eaten\n", game->moves, game->collected, game->coin);
		cleanup(game, 0);
	}
	if (next != '1' && next != 'E')
	{
		if (next == 'C')
			game->collected++;
		game->map[y][x - 1] = game->map[y][x];
		game->map[y][x] = '0';
		game->p_pos[0] = x - 1;
		game->moves++;
		ft_printf("Moves: %d With (%d/%d) Sheeps Eaten\n", game->moves, game->collected, game->coin);
		return (0);
	}
	return (0);
}
