#include "solong.h"

int	loop_init(t_game_info *game)
{
	int	x;
	int	y;

	y = 0;

	game->frame++;
	if (game->frame > 3)
		game->frame = 0;
	while (y < game->grid->rows)
	{
		x = 0;
		while (x < game->grid->cols)
		{
			if (game->map[y][x] == 'N')
			{
				put_image(game, game->map[y][x], x , y); //fgure out fram and tha
			}
			x++;
		}
		y++;
	}
	return (1);
}