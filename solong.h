/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:14 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 00:47:35 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

//#include "minilibx-linux/mlx.h"
# include "gnl/get_next_line.h"
#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "utils/utils.h"

# include <string.h>
//#include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define WIDTH 500
# define HEIGHT 500

typedef struct vars
{
	int	p_pos[2];
	int	player;
	int	exit;
	int	coin;
}	t_vars;

typedef struct map
{
	char	grid[10][10];
	int		width;
	int		height;
}	t_map;

/* floodfill funcs */
void	flood_fill(char **map, int x, int y);
int		check_reachability(char **map, int *rows, int *cols);
int		all_is_reachable(int x, int y, int rows, int cols);

/* map_checker funcs */
void	free_map(char **map, int rows);
int		error_handling(t_vars *variables);
void	update_stats(char cell, int i, int j, t_vars *variables);
int		check_boundries(int rows, int cols, char **map);
int		is_map_valid(char **map, int rows, int cols, t_vars *variables);

/* map making funcs */
int		count_lines_and_columns(int fd, int *rows, int *cols);
char	**allocate_map(int rows, int cols);
void	populate_map(int fd, char **map, int rows, int cols);
char	**make_map(int fd, int *rows, int *cols);

/* extern funcs */
char	*get_next_line(int fd);

#endif