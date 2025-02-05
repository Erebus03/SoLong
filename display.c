#include "solong.h"

void	put_image(t_game_info *game, char cell, int x,  int y)
{
	if (cell == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->imgs->wall, x, y);
	else if (cell == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->imgs->coin, x, y);
	else if (cell == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->imgs->p_left, x, y);
	else if (cell == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->imgs->exit, x, y);
}

void	get_imgs(t_img *img, void *mlxptr)
{
	int x;

	/* wall */
	img->wall = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	/* coin */
	img->coin[0] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->coin[1] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	/* player */
	img->p_up[0] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_up[1] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_up[2] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_down[0] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_down[1] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_down[2] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_right[0] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_right[1] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_right[2] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_left[0] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_left[1] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	img->p_left[2] = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
	/* exit */
	img->exit = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &x, &x);
}

void	win_init(t_game_info *game)
{
	int	x;
	int	y;
	game->imgs = malloc(sizeof(t_img));
	if (!game->imgs)
	{
		ft_printf("Error:\nAllocation failed for t_imgs\n");
		return ;
	}
	get_imgs(game->imgs, game->mlx);
	game->win = mlx_new_window(game->mlx, game->grid->cols * 50, game->grid->rows * 50, "window");

	x = 0;
	while(x < game->grid->cols)
	{
		y = 0;
		while(y < game->grid->rows)
		{
			put_image(game, game->map[y][x], x, y);
		}
	}
}