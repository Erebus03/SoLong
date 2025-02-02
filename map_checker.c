/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:40 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 20:59:31 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	error_handling(t_vars *vars)
{
	if (vars->player != 1)
	{
		ft_printf("Error: Map must contain one P. Found: %d\n", vars->player);
		return (0);
	}
	if (vars->exit != 1)
	{
		ft_printf("Error: Map must contain one E. Found: %d\n", vars->exit);
		return (0);
	}
	if (vars->coin < 1)
	{
		ft_printf("Error: Map must contain >= 1 C. Found: %d\n", vars->coin);
		return (0);
	}
	return (1);
}

void	update_stats(char cell, int i, int j, t_vars *variables)
{
	if (cell == 'P')
	{
		variables->player++;
		variables->p_pos[0] = j;
		variables->p_pos[1] = i;
	}
	else if (cell == 'E')
		variables->exit++;
	else if (cell == 'C')
		variables->coin++;
}

void	some(char **map, t_vars *vars, int rows, int cols)
{
	int		i;
	int		j;
	char	cell;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			cell = map[i][j];
			if (cell == 'C' || cell == 'E' || cell == 'P')
				update_stats(cell, i, j, vars);
			j++;
		}
		i++;
	}
}

int	check_boundries(int rows, int cols, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
			{
				if (map[i][j] != '1')
				{
					ft_printf("Error: need a wall at (%d, %d)\n", i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_map_valid(char **map, int rows, int cols, t_vars *var)
{
	if (check_boundries(rows, cols, map) == 0)
		return (0);
	some(map, var, rows, cols);
	if (error_handling(var) == 0)
		return (0);
	if (all_is_reachable(var->p_pos[0], var->p_pos[1], rows, cols) == 0)
	{
		ft_printf("exit/coin aint reachable!\n");
		return (0);
	}
	return (1);
}
