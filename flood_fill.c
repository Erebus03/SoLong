/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:53 by araji             #+#    #+#             */
/*   Updated: 2025/02/04 06:32:08 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_reachability(char **map, t_game *game)
{
	int (i), (j), (return_value);
	i = 0;
	return_value = 1;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (map[i][j] == 'C')
			{
				//remove this later
				ft_printf("Error\nPosition(%d,%d) is not reachable\n", i, j);
				return_value = 0;
			}
			j++;
		}
		i++;
	}
	return (return_value);
}

char	**copy_map(t_game *game)
{
	char	**map;

	int (i), (j);
	map = malloc(game->rows * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < game->rows)
	{
		map[i] = malloc((game->cols + 1) * sizeof(char));
		if (!map[i])
			return (NULL);
		i++;
	}
	i = -1;
	while (++i < game->rows)
	{
		j = -1;
		while (++j < game->cols)
			map[i][j] = game->map[i][j];
		map[i][j] = '\0';
	}
	return (map);
}

void	flood_fill(t_game *game, char **map_copy, int x, int y)
{
	char	cell;

	if (x < 0 || x >= game->cols || y < 0 || y >= game->rows)
		return ;
	cell = map_copy[y][x];
	if (cell == '1' || cell == 'V' || cell == 'N' || cell == 'E')
		return ;
	map_copy[y][x] = 'V';
	flood_fill(game, map_copy, x - 1, y);
	flood_fill(game, map_copy, x + 1, y);
	flood_fill(game, map_copy, x, y + 1);
	flood_fill(game, map_copy, x, y - 1);
}

int	all_is_reachable(t_game *game)
{
	char	**map_copy;

	int (ret), (i);
	i = 0;
	map_copy = NULL;
	map_copy = copy_map(game);
	if (!map_copy)
	{
		free_map(game->rows, map_copy);
		cleanup(game, 1);
	}
	flood_fill(game, map_copy, game->p_pos[0], game->p_pos[1]);
	ret = check_reachability(map_copy, game);
	while (i < game->rows)
		free(map_copy[i++]);
	free(map_copy);
	return (ret);
}
