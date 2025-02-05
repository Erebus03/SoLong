#include "solong.h"

void	win_init(t_game_info *game)
{
	game->win = mlx_new_window(game->mlx, game->grid->cols * 50,
		game->grid->rows * 50, "window");
	
}