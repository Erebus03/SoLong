#include "solong.h"

int	put_image(t_game_info *game, char cell, int x,  int y)
{
	int	ret;

	ret = -2;
	if (cell == '1')
		ret =mlx_put_image_to_window(game->mlx, game->win, game->imgs->wall , x * 50, y * 50);
	if (cell == '0')
		ret = mlx_put_image_to_window(game->mlx, game->win, game->imgs->floor , x * 50, y * 50);
	else if (cell == 'C')
	{
		ret = mlx_put_image_to_window(game->mlx, game->win, game->imgs->coin[0], x * 50, y * 50);
		ret = mlx_put_image_to_window(game->mlx, game->win, game->imgs->coin[1], x * 50, y * 50);
	}
	else if (cell == 'O')
	{
		ret = mlx_put_image_to_window(game->mlx, game->win, game->imgs->coin[0], x * 50, y * 50);
		ret = mlx_put_image_to_window(game->mlx, game->win, game->imgs->coin[1], x * 50, y * 50);
	}
	else if (cell == 'P')
	{
		ret = mlx_put_image_to_window(game->mlx, game->win, game->imgs->p_left[0], x * 50, y * 50);
	}
	else if (cell == 'E')
		ret = mlx_put_image_to_window(game->mlx, game->win, game->imgs->exit, x * 50, y * 50);
	return ret;
}

int	win_init(t_game_info *game)
{
	int	x;
	int	y;

	if (!assigne_images(game->imgs, game->mlx))
	{
		ft_printf("Error\nCouldn't assigne images!\n");
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->grid->cols * 50, game->grid->rows * 50, "window");
	x = 0;
	while(x < game->grid->rows)
	{
		y = 0;
		while(y < game->grid->cols)
		{
			// ft_printf("+++  >%d< +++\n", put_image(game, game->map[y][x], x, y));
			if (put_image(game, game->map[y][x], x, y) == -2)
				return 0;
			y++;
		}
		x++;
	}
	return (1);
}