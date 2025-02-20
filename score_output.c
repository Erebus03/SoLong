#include "solong.h"

void	update_score_display(t_game *game)
{
	int		msg_y;
	char	*coins_eaten;
	char	*moves;

	msg_y = game->rows * 50 + 10;
	moves = display_moves(game);
	coins_eaten = display_coins_eaten(game);
	mlx_put_image_to_window(game->mlx, game->win, game->imgs->empty_bg, 0, game->rows * 50);
	if (moves)
	{
		mlx_string_put(game->mlx, game->win, 3, msg_y, 0xFFFFFF, moves);
		free(moves);
	}
	if (coins_eaten)
	{
		mlx_string_put(game->mlx, game->win, 3, msg_y + 15, 0xFFFFFF, coins_eaten);
		free(coins_eaten);
	}
}
char *display_moves(t_game *game)
{
    char *msg;
    char *moves;

    moves = ft_itoa(game->moves);
    msg = ft_strjoin("Moves: ", moves);
    free(moves);
    return (msg);
}

char *display_coins_eaten(t_game *game)
{
    char *msg;
    char *collected;
    char *coin;
    char *temp;

    collected = ft_itoa(game->collected);
    coin = ft_itoa(game->coin);
    temp = ft_strjoin("Eaten (", collected);
    free(collected);
    msg = ft_strjoin(temp, "/");
    free(temp);
    temp = ft_strjoin(msg, coin);
    free(msg);
    free(coin);
    msg = ft_strjoin(temp, ") Sheeps");
    free(temp);
    return (msg);
}

void	p_direction(t_game *game)
{
	int (x), (y);
	x = game->p_pos[0];
	y = game->p_pos[1];
	if (game->map[y][x - 1] == '1')
		game->direction = 0; //head to right
	else
		game->direction = 1;
}