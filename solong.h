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
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_paths
{
	char	*floor;
	char	*wall;
	char	*exit;
	char	*empty_bg;
	char	*chained;
	char	*enemy[2];
	char	*coin[2];
	char	*attack[4];
	char	*p_right[2];
	char	*p_left[2];
}	t_paths;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*exit;
	void	*empty_bg;
	void	*chained;
	void	*enemy[2];
	void	*coin[2];
	void	*p_right[2];
	void	*p_left[2];
	void	*attack[4];

}	t_img;

typedef struct s_game
{
	int		fd;
	int		rows;
	int		cols;
	int		coin;
	int		collected;
	int		exit;
	int		enemy;
	int		player;
	int		direction;
	int		p_pos[2];
	int		moves;
	int		frame;
	int		c_delay;
	int		n_delay;
	int		p_delay;
	int		c_frame;
	int		n_frame;
	int		p_frame;
	char	**map;
	char	*filename;
	void	*mlx;
	void	*win;
	t_img	*imgs;
}	t_game;

/* floodfill.c */
void	flood_fill(t_game *game, char **map_copy, int x, int y);
int		check_reachability(char **map, t_game *game);
int		all_is_reachable(t_game *game);

/* map_checker.c */
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
int		cleanup(t_game *game, int exitmode);
int		check_args(int ac, char **av);
int		init_game(t_game *game);
int		render_map(t_game *game, t_paths *paths);

/* display.c*/
int		win_init(t_game *game, t_paths	**paths);
int		put_image(t_game *g, char cell, int x, int y);
int		assigne_paths(t_paths **p);
int		loop_init(t_game *game);
int		key_input(int keycode, t_game *game);

/* load_images.c */
int		assigne_images(t_game *game, t_paths **paths);
int		assigne_enemy_and_attack(t_img *img, void *mlxptr,
			t_paths *path, int k);
int		assigne_player_positions(t_img *img, void *mlxptr,
			t_paths *path, int k);
int		assigne_other(t_img *img, void *mlxptr, t_paths *path, int k);
void	free_images(t_img *img, void *mlx_ptr);

/* mevemnt.c */
int		move_left(t_game *game, int x, int y);
int		move_right(t_game *game, int x, int y);
int		move_down(t_game *game, int x, int y);
int		move_up(t_game *game, int x, int y);
void	attack(t_game *game, int x, int y);

/* score_display.c */
char	*display_coins_eaten(t_game *game);
char	*display_moves(t_game *game);
void	update_score_display(t_game *game);

#endif