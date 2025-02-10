#include "solong.h"

int move_up(t_game_info *game, int x, int y)
{
	if (game->map[y - 1][x] == 'N')
		exit(1);
	if (game->map[y - 1][x] != '1' && game->map[y - 1][x] != 'E')
	{
		if (game->map[y - 1][x] == 'C')
			game->var->coin--;
		game->map[y - 1][x] = game->map[y][x];
		game->map[y][x] = '0';
		game->var->p_pos[1] = y - 1;
		return 0;
	}
	printf("wall or exit\n");
	return 0;
}

int move_down(t_game_info *game, int x, int y)
{
	if (game->map[y + 1][x] == 'N')
		exit(1);
	if (game->map[y + 1][x] != '1' && game->map[y + 1][x] != 'E')
	{
		if (game->map[y + 1][x] == 'C')
			game->var->coin--;
		game->map[y + 1][x] = game->map[y][x];
		game->map[y][x] = '0';
		game->var->p_pos[1] = y + 1;
		return 0;
	}
	printf("wall or exit\n");
	return 0;
}

int move_right(t_game_info *game, int x, int y)
{
	if (game->map[y][x + 1] == 'N')
		exit(1);
	if (game->map[y][x + 1] != '1' && game->map[y][x + 1] != 'E')
	{
		if (game->map[y][x + 1] == 'C')
			game->var->coin--;
		game->map[y][x + 1] = game->map[y][x];
		game->map[y][x] = '0';
		game->var->p_pos[0] = x + 1;
		return 0;
	}
	printf("wall or exit\n");
	return 0;
}

int move_left(t_game_info *game, int x, int y)
{
	if (game->map[y][x - 1] == 'N')
		exit(1);
	if (game->map[y][x - 1] != '1' && game->map[y][x - 1] != 'E')
	{
		if (game->map[y][x - 1] == 'C')
			game->var->coin--;
		game->map[y][x - 1] = game->map[y][x];
		game->map[y][x] = '0';
		game->var->p_pos[0] = x - 1;
		return 0;
	}
	printf("wall or exit\n");
	return 0;
}

// int	move_player(t_game_info *game, char direction)
// {
// 	int x = game->var->p_pos[0];
// 	int y = game->var->p_pos[1];
// 	printf("player(%d,%d)\n", x, y);
// 	if (direction == 'u')
// 		move_up(game, x, y);
// 	if (direction == 'd')
// 		move_down(game, x, y);
// 	if (direction == 'r')
// 		move_right(game, x, y);
// 	if (direction == 'l')
// 		move_left(game, x, y);
// 	return 0;
// }