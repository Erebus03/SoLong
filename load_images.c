/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:38:42 by araji             #+#    #+#             */
/*   Updated: 2025/02/06 13:38:42 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	free_images(t_img *img, void *mlxptr)
{
	if (img)
	{
		(void)mlxptr;
		// free_player(img, mlxptr);
		// free_enemy_attack(img, mlxptr);
		// free_c_w_f_e(img, mlxptr);
	}
	return ;
}

int	assigne_other(t_img *img, void *mlxptr, t_paths *path, int k)
{
	img->coin[0] = mlx_xpm_file_to_image(mlxptr, path->coin[0], &k, &k);
	img->coin[1] = mlx_xpm_file_to_image(mlxptr, path->coin[1], &k, &k);
	if (!(img->coin[0]) || !(img->coin[1]))
	{
		free_images(img, mlxptr);
		return (0);
	}
	img->wall = mlx_xpm_file_to_image(mlxptr, path->wall, &k, &k);
	img->floor = mlx_xpm_file_to_image(mlxptr, path->floor, &k, &k);
	img->exit = mlx_xpm_file_to_image(mlxptr, path->exit, &k, &k);
	if (!(img->wall) || !(img->floor) || !(img->exit))
	{
		free_images(img, mlxptr);
		return (0);
	}
	return (1);
}

int	assigne_player_positions(t_img *img, void *mlxptr, t_paths *path, int k)
{
	img->p_up[0] = mlx_xpm_file_to_image(mlxptr, path->p_up[0], &k, &k);
	img->p_up[1] = mlx_xpm_file_to_image(mlxptr, path->p_up[1], &k, &k);
	img->p_down[0] = mlx_xpm_file_to_image(mlxptr, path->p_down[0], &k, &k);
	img->p_down[1] = mlx_xpm_file_to_image(mlxptr, path->p_down[1], &k, &k);
	if (!(img->p_up[0]) || !(img->p_up[1])
		|| !(img->p_down[0]) || !(img->p_down[1]))
	{
		free_images(img, mlxptr);
		return (0);
	}
	img->p_right[0] = mlx_xpm_file_to_image(mlxptr, path->p_right[0], &k, &k);
	img->p_right[1] = mlx_xpm_file_to_image(mlxptr, path->p_right[1], &k, &k);
	img->p_left[0] = mlx_xpm_file_to_image(mlxptr, path->p_left[0], &k, &k);
	img->p_left[1] = mlx_xpm_file_to_image(mlxptr, path->p_left[1], &k, &k);
	if (!(img->p_right[0]) || !(img->p_right[1])
		|| !(img->p_left[0]) || !(img->p_left[1]))
	{
		free_images(img, mlxptr);
		return (0);
	}
	return (1);
}

int	assigne_enemy_and_attack(t_img *img, void *mlxptr, t_paths *path, int k)
{
	img->enemy[0] = mlx_xpm_file_to_image(mlxptr, path->enemy[0], &k, &k);
	img->enemy[1] = mlx_xpm_file_to_image(mlxptr, path->enemy[1], &k, &k);
	if (!(img->enemy[0]) || !(img->enemy[1]))
	{
		free_images(img, mlxptr);
		return (0);
	}
	img->attack[0] = mlx_xpm_file_to_image(mlxptr, path->attack[0], &k, &k);
	img->attack[1] = mlx_xpm_file_to_image(mlxptr, path->attack[1], &k, &k);
	img->attack[2] = mlx_xpm_file_to_image(mlxptr, path->attack[2], &k, &k);
	img->attack[3] = mlx_xpm_file_to_image(mlxptr, path->attack[3], &k, &k);
	if (!(img->attack[0]) || !(img->attack[1]) || !(img->attack[2])
		|| !(img->attack[3]))
	{
		free_images(img, mlxptr);
		return (0);
	}
	return (1);
}

int	assigne_images(t_img **imgs, void *mlx_ptr, t_paths **path)
{
	int	k;

	k = 0;
	*imgs = malloc(sizeof(t_img));
	if (!*imgs)
	{
		ft_printf("Error:\nAllocation failed for t_imgs\n");
		return (0);
	}
	if (!assigne_player_positions(*imgs, mlx_ptr, *path, k))
		return (0);
	if (!assigne_enemy_and_attack(*imgs, mlx_ptr, *path, k))
		return (0);
	if (!assigne_other(*imgs, mlx_ptr, *path, k))
		return (0);
	return (1);
}
