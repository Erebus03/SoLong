#include "solong.h"
int	put_image(t_game_info *game, char cell, int x,  int y)
{
	int	ret;

	if(!game->mlx || !game->win || !game->imgs->wall)
	{
		ft_printf("game.mlx || game.win || game->imgs->wall not valid\n");
		return (0);
	}
	ret = 0;
	printf("cell: %c\n", cell);
	if (cell == '1')
	{
		ret = mlx_put_image_to_window(game->mlx, game->win, game->imgs->wall , x * 50, y * 50);
		printf("ret %d\n", ret);
	}
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

	if (!assigne_images(&game->imgs, game->mlx))
	{
		ft_printf("Error\nCouldn't assigne images!\n");
		return (0);
	}
	write(1, "check1\n", 7);
		
	if (1) {
		write(1, "check\n", 6);
		if (!game->imgs->wall)
			write(1, "img.wall\n", 9);
		if (game->imgs->floor)
			write(1, "img.wall\n", 9);
		if (game->imgs->exit)
			write(1, "img.wall\n", 9);
		
		int	i;
		i = 0;
		while(i < 3)
			if (game->imgs->p_up[i++])
				write(1, "img.wall\n", 9);
		write(1, "check\n", 6);
		i = 0;
		while(i < 3)
			if (game->imgs->p_down[i++])
				write(1, "img.wall\n", 9);
		i = 0;
		write(1, "check\n", 6);
		while(i < 3)
			if (game->imgs->p_right[i++])
				write(1, "img.wall\n", 9);
		write(1, "check\n", 6);
		i = 0;
		while(i < 3)
			if (game->imgs->p_left[i++])
				write(1, "img.wall\n", 9);
		write(1, "check\n", 6);
		i = 0;
		while (i < 4)
			if (game->imgs->attack[i++])
				write(1, "img.wall\n", 9);
		write(1, "check\n", 6);
		i = 0;
		while (i < 2)
			if (game->imgs->enemy[i++])
				write(1, "img.wall\n", 9);
		write(1, "check\n", 6);
		i = 0;
		while (i < 2)
			if (game->imgs->coin[i++])
				write(1, "img.wall\n", 9);
		write(1, "checkf\n", 7);
		}

	game->win = mlx_new_window(game->mlx, game->grid->cols * 50, game->grid->rows * 50, "window");
	if (game->win)
		printf("game.win good\n");
	x = 0;
	while(x < game->grid->rows)
	{
		y = 0;
		while(y < game->grid->cols)
		{
			if (!put_image(game, game->map[y][x], x, y))
				return 0;
			y++;
		}
		x++;
	}
	return (1);
}
