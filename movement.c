#include "solong.h"

int move_up(t_game *game, int x, int y)
{
	char	next;

	next = game->map[y - 1][x];
	if ((next == 'E' && game->coin == 0) || next == 'N')
		cleanup(game, 0);
	if (next != '1' && next != 'E')
	{
		if (next == 'C')
			game->coin--;
		game->map[y - 1][x] = game->map[y][x];
		game->map[y][x] = '0';
		game->p_pos[1] = y - 1;
		return 0;
	}
	return 0;
}

int move_down(t_game *game, int x, int y)
{
	char	next;

	next = game->map[y + 1][x];
	if ((next == 'E' && game->coin == 0) || next == 'N')
		cleanup(game, 0);
	if (next != '1' && next != 'E')
	{
		if (next == 'C')
			game->coin--;
		game->map[y + 1][x] = game->map[y][x];
		game->map[y][x] = '0';
		game->p_pos[1] = y + 1;
		return 0;
	}
	return 0;
}

int move_right(t_game *game, int x, int y)
{
	char	next;

	next = game->map[y][x + 1];
	if ((next == 'E' && game->coin == 0) || next == 'N')
		cleanup(game, 0);
	if (next != '1' && next != 'E')
	{
		if (next == 'C')
			game->coin--;
		game->map[y][x + 1] = game->map[y][x];
		game->map[y][x] = '0';
		game->p_pos[0] = x + 1;
		return (0);
	}
	return (0);
}

int move_left(t_game *game, int x, int y)
{
	char	next;

	next = game->map[y][x - 1];
	if ((next == 'E' && game->coin == 0) || next == 'N')
		cleanup(game, 0);	
	if (next != '1' && next != 'E')
	{
		if (next == 'C')
			game->coin--;
		game->map[y][x - 1] = game->map[y][x];
		game->map[y][x] = '0';
		game->p_pos[0] = x - 1;
		return (0);
	}
	return (0);
}
