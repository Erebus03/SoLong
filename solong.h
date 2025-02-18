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

# include "../minilibx-linux/mlx.h"
# include "utils/utils.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_paths
{
	char	*floor;
	char	*wall;
	char	*exit;
	char	*chained;
	char	*enemy[2];
	char	*coin[2];
	char	*attack[4];
	char	*p_up[2];
	char	*p_down[2];
	char	*p_right[2];
	char	*p_left[2];
}	t_paths;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*exit;
	void	*chained;
	void	*enemy[2];
	void	*coin[2];
	void	*p_up[2];
	void	*p_down[2];
	void	*p_right[2];
	void	*p_left[2];
	void	*attack[4];

}	t_img;

typedef struct s_game
{
	int		rows;
	int		cols;
	int		p_pos[2];
	int		player;
	int		enemy;
	int		exit;
	int		coin;
	char	**map;
	char	*filename;
	t_img	*imgs;
	int		fd;
	void	*mlx;
	void	*win;
	int		frame;
}	t_game;

/* floodfill.c */
void	flood_fill(t_game *game, char **map_copy, int x, int y);
int		check_reachability(char **map, t_game *game);
int		all_is_reachable(t_game *game);

/* map_checker.c */
// int		error_handling(t_game *game);
int		check_cells(t_game *game);
int		check_boundries(t_game *game);
int		is_map_valid(t_game *game);

/* map maker.c */
int		count_lines_and_columns(t_game *game);
char	**allocate_map(t_game *game);
int		populate_map(t_game *game);
void	make_map(t_game *game);
void	free_map(int rows, char **map);

/* main */
int		init_game(t_game *game);
int		check_args(int ac, char **av, t_game *game);
void	cleanup(t_game *game, int exitmode);
int		render_map(t_game *game, t_paths *paths);

/* display.c*/
int		win_init(t_game *game, t_paths	**paths);
int		put_image(t_game *g, char cell, int x, int y);
void	assigne_paths(t_paths **p);
int		loop_init(t_game *game);
int		key_input(int keycode, t_game *game);

/* load_images.c */
int		assigne_images(t_game *game, t_paths **paths);
int		assigne_enemy_and_attack(t_img *img, void *mlxptr, t_paths *path, int k);
int		assigne_player_positions(t_img *img, void *mlxptr, t_paths *path, int k);
int		assigne_other(t_img *img, void *mlxptr, t_paths *path, int k);
void	free_images(t_img *img, void *mlx_ptr);

/* free_iamges.c */
// void	free_player(t_img *img, void *mlxptr);
// void	free_enemy_attack(t_img *img, void *mlxptr);
// void	free_c_w_f_e(t_img *img, void *mlxptr);

/* mevemnt.c */
// int	move_player(t_game *game, char direction);
int move_left(t_game *game, int x, int y);
int move_right(t_game *game, int x, int y);
int move_down(t_game *game, int x, int y);
int move_up(t_game *game, int x, int y);

#endif