#ifndef SOLONG_H
# define SOLONG_H

#include "minilibx-linux/mlx.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

# define WIDTH 500
# define HEIGHT 500

typedef struct vars {
	int p_pos[2];
	int player;
	int exit;
	int coin;
} vars;

typedef struct {
    char grid[10][10];
    int width;
    int height;
} Map;


int	all_is_reachable(int, int, int, int);
void    update_stats(char cell, int i, int j, vars *variables);
int    error_handling(vars *variables);
int check_boundries(int rows, int cols, char **map);
void    flood_fill(char map[5][11], int x, int y);
void free_map(char **map, int rows);
char **make_map(int fd, int *rows, int *cols);
char *get_next_line(int fd);
int	map_is_valid(int fd);

#endif