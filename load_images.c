#include "solong.h"

void free_images(t_img *img)
{
	return ;
}

int	assigne_other(t_img *img, void *mlxptr, int k)
{
	img->wall = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &k, &k);
	if (!img->wall)
		return (0);
	img->floor = mlx_xpm_file_to_image(mlxptr, "pics/floor.xpm", &k, &k);
	if (!img->floor)
		return (0);
	img->exit = mlx_xpm_file_to_image(mlxptr, "pics/wall.xpm", &k, &k); //download exit
	if (!img->exit)
		return (0);
	img->coin[0] = mlx_xpm_file_to_image(mlxptr, "pics/sheep/sheep1.xpm", &k, &k);
	if (!img->coin[0])
		return (0);
	img->coin[1] = mlx_xpm_file_to_image(mlxptr, "pics/sheep/sheep1.xpm", &k, &k); //sheep2
	return (1);
}

int	assigne_player_positions(t_img *img, void *mlxptr, int k)
{
	/* player */
	img->p_up[0] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	if (!img->p_up[0])
		return (0);
	img->p_up[1] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	img->p_up[2] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	img->p_down[0] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	if (!img->p_down[0])
		return (0);
	img->p_down[1] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	img->p_down[2] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	img->p_right[0] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	if (!img->p_right[0])
		return (0);
	img->p_right[1] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	img->p_right[2] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	img->p_left[0] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	img->p_left[1] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	img->p_left[2] = mlx_xpm_file_to_image(mlxptr, "pics/monster/monster1.xpm", &k, &k);
	if (!img->p_left[0] || !img->p_left[1])
	{
		free_images(img);
		return (0);
	}
	return (1);
}

int	assigne_enemy_and_attack(t_img *img, void *mlxptr, int k)
{
	/* standing */
	img->enemy[0] = mlx_xpm_file_to_image(mlxptr, "pics/enemy/enemy1.xpm", &k, &k);
	img->enemy[1] = mlx_xpm_file_to_image(mlxptr, "pics/enemy/enemy2.xpm", &k, &k);
	if (!img->enemy[0] || !img->enemy[1])
		return (0);
	/* attack */
	img->attack[0] = mlx_xpm_file_to_image(mlxptr, "pics/attack/attack1.xpm", &k, &k);
	img->attack[1] = mlx_xpm_file_to_image(mlxptr, "pics/attack/attack2.xpm", &k, &k);
	img->attack[2] = mlx_xpm_file_to_image(mlxptr, "pics/attack/attack3.xpm", &k, &k);
	img->attack[3] = mlx_xpm_file_to_image(mlxptr, "pics/attack/attack4.xpm", &k, &k);
	if (!img->attack[0] || !img->attack[1] || !img->attack[2] || !img->attack[3])
	{
		free_images(img);
		return (0);
	}
	return (1);
}

int	assigne_images(t_img *imgs, void *mlx_ptr)
{
	int k;

	k = 0;
	imgs = malloc(sizeof(t_img));
	if (!imgs)
	{
		ft_printf("Error:\nAllocation failed for t_imgs\n");
		return (0);
	}
	if (!assigne_player_positions(imgs, mlx_ptr, k))
		return (0);
	if (!assigne_enemy_and_attack(imgs, mlx_ptr, k))
		return (0);
	if (!assigne_other(imgs, mlx_ptr, k))
		return (0);
	return (1);
}