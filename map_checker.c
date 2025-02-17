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

// int	error_handling(t_game *game)
// {
// 	if (game->player != 1 || game->exit != 1
// 		|| game->coin < 1 || game->enemy < 1)
// 	{
// 		ft_printf("Error\nMap elements ain't valid (1P, 1E, >=1C, >=1N)");
// 		cleanup(game, 1);
// 		exit(1);
// 	}
// 	return (1);
// }

// void	update_stats(char cell, int i, int j, t_game *game)
// {
// 	if (cell == 'P')
// 	{
// 		game->player++;
// 		game->p_pos[0] = j;
// 		game->p_pos[1] = i;
// 	}
// 	else if (cell == 'E')
// 		game->exit++;
// 	else if (cell == 'C')
// 		game->coin++;
// 	else if (cell == 'N')
// 		game->enemy++;
// }

int	check_cells(t_game *game)
{
	int		(i), (j);
	char	cell;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			cell = game->map[i][j];
			//	ft_printf("Error\n[%c] is no valid chracter!\n", cell);
			if (cell != 'C' && cell != 'P' && cell != 'E' && cell != '0' && cell != '1' && cell != 'N')
				return (0);
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
			j++;
		}
		i++;
	}
	return (1);
}
	// if (cell == 'C' || cell == 'E' || cell == 'P' || cell == 'N')
	// 	update_stats(cell, i, j, vars);
	
int	check_boundries(t_game *game)
{
	int	i;
	int	j;

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
					cleanup(game, 1);// removed areturn here to exit with cleaup
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
		ft_printf("Error\nMap elements ain't valid (1P, 1E, >=1C, >=1N)");
		cleanup(game, 1);
	}
	if (all_is_reachable(game) == 0) //flood_fill
		return (0);
	return (1);
}
