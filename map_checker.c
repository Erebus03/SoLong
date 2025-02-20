/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:40 by araji             #+#    #+#             */
/*   Updated: 2025/02/04 06:39:54 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	is_element_valid(char element)
{
	if (element != '1' && element != '0' && element != 'P'
		&& element != 'C' && element != 'E' && element != 'N')
	{
		ft_printf("Error\n[%c] is no valid chracter!\n", element);
		return (0);
	}
	return (1);
}

void	update_stats(char cell, int i, int j, t_game *game)
{
	if (!cell || !game)
		return ;
	if (cell != '1' && cell != '0' && cell != 'P'
		&& cell != 'C' && cell != 'E' && cell != 'N')
	{
		ft_printf("Error\nElement in (%d,%d) is no valid chracter!\n", i, j);
		cleanup(game, 1);
	}
	if (cell == 'P')
	{
		game->player++;
		game->p_pos[0] = j;
		game->p_pos[1] = i;
	}
	else if (cell == 'E')
		game->exit++;
	else if (cell == 'C')
		game->coin++;
	else if (cell == 'N')
		game->enemy++;
}

int	check_cells(t_game *game)
{
	int (i), (j);
	if (!game)
		return (0);
	i = -1;
	while (++i < game->rows)
	{
		j = -1;
		while (++j < game->cols)
			update_stats(game->map[i][j], i, j, game);
	}
	return (1);
}

int	check_boundries(t_game *game)
{
	int (i), (j);
	i = 0;
	j = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (i == 0 || i == game->rows - 1 || j == 0 || j == game->cols - 1)
			{
				if (game->map[i][j] != '1')
				{
					ft_printf("Error\nNeed a wall at (%d, %d)\n", i, j);
					cleanup(game, 1);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_map_valid(t_game *game)
{
	if (check_boundries(game) == 0)
		return (0);
	if (!check_cells(game))
		return (0);
	if (game->player != 1 || game->exit != 1
		|| game->coin < 1 || game->enemy < 1)
	{
		ft_printf("Error\nMap elements ain't valid (1P, 1E, >=1C, >=1N)\n");
		cleanup(game, 1);
	}
	if (all_is_reachable(game) == 0)
		return (0);
	return (1);
}
