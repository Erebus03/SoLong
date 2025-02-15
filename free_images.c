/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:38:33 by araji             #+#    #+#             */
/*   Updated: 2025/02/06 13:38:33 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	free_player(t_img *img, void *mlxptr)
{
	int	(i), (n_pics);

	i = -1;
	n_pics = 2;
	if (!img)
		return ;
	while (++i < n_pics)
		if (img->p_up[i])
			mlx_destroy_image(mlxptr, img->p_up[i]);
	i = -1;
	while (++i < n_pics)
		if (img->p_down[i])
			mlx_destroy_image(mlxptr, img->p_down[i]);
	i = -1;
	while (++i < n_pics)
		if (img->p_right[i])
			mlx_destroy_image(mlxptr, img->p_right[i]);
	i = -1;
	while (++i < n_pics)
		if (img->p_left[i])
			mlx_destroy_image(mlxptr, img->p_left[i]);
}

void	free_enemy_attack(t_img *img, void *mlxptr)
{
	int	(i), (enemy_pics), (attack_pics);

	if (!img)
		return ;
	i = -1;
	attack_pics = 4;
	enemy_pics = 2;
	while (++i < enemy_pics)
		if (img->enemy[i])
			mlx_destroy_image(mlxptr, img->enemy[i]);
	i = -1;
	while (++i < attack_pics)
		if (img->attack[i])
			mlx_destroy_image(mlxptr, img->attack[i]);
}

void	free_c_w_f_e(t_img *img, void *mlxptr)
{
	int	i;
	int	n_coin;

	if (!img)
		return ;
	i = -1;
	n_coin = 2;
	if (img->wall)
		mlx_destroy_image(mlxptr, img->wall);
	if (img->exit)
		mlx_destroy_image(mlxptr, img->exit);
	if (img->floor)
		mlx_destroy_image(mlxptr, img->floor);
	while (++i < n_coin)
		if (img->coin[i])
			mlx_destroy_image(mlxptr, img->coin[i]);
}
