/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:14 by araji             #+#    #+#             */
/*   Updated: 2025/02/05 10:29:23 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include "minilibx-linux/mlx.h"
# include "gnl/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "utils/utils.h"

# include <string.h>
//#include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_vars
{
	int		p_pos[2];
	int		player;
	int		exit;
	int		coin;
}	t_vars;

typedef struct s_map
{
	int		rows;
	int		cols;
}	t_map;

typedef struct s_game
{
    char    **map;
    t_map   *grid;
    t_vars  *var;
    int     fd;
	void	*mlx;
	void	*win;
}   t_game_info;

/* floodfill funcs */
void	flood_fill(t_map *grid, char **map, int x, int y);

int		check_reachability(char **map, t_map *grid);

int		all_is_reachable(int x, int y, t_map *grid, char *filename);

/* map_checker funcs */
void	free_map(char **map, int rows);

int		error_handling(t_vars *variables);

void	update_stats(char cell, int i, int j, t_vars *variables);

int		check_boundries(int rows, int cols, char **map);

int		is_map_valid(char **map, t_map *grid,
			t_vars *variables, char *filename);

int		check_cells(char **map, t_vars *vars, int rows, int cols);

/* map making funcs */
int		count_lines_and_columns(int fd, t_map *grid);

char	**allocate_map(int rows, int cols);

int		populate_map(int fd, char **map, int rows, int cols);

char	**make_map(int fd, t_map *grid, char *filename);

/* main */
int	init_game(t_game_info *game, char *filename);

int	check_args(int ac, char **av, t_game_info *game);

void    cleanup(t_game_info *game);


/* display.c*/
void	win_init(t_game_info *game);

void	render_map(t_game_info *game);

#endif