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
	int	i;
	int	n_pics;

	i = -1;
	n_pics = 2;
	if (!img)
		return ;
	while (++i < n_pics)
		if (img->p_up[i])
			mlx_destroy_image(img->p_up[i], mlxptr);
	i = -1;
	while (++i < n_pics)
		if (img->p_down[i])
			mlx_destroy_image(img->p_down[i], mlxptr);
	i = -1;
	while (++i < n_pics)
		if (img->p_right[i])
			mlx_destroy_image(img->p_right[i], mlxptr);
	i = -1;
	while (++i < n_pics)
		if (img->p_left[i])
			mlx_destroy_image(img->p_left[i], mlxptr);
}

void	free_enemy_attack(t_img *img, void *mlxptr)
{
	int	i;
	int	enemy_pics;
	int	attack_pics;

	if (!img)
		return ;
	i = -1;
	attack_pics = 2;
	enemy_pics = 4;
	while (++i < enemy_pics)
		if (img->enemy[i])
			mlx_destroy_image(img->enemy[i], mlxptr);
	i = -1;
	while (++i < attack_pics)
		if (img->attack[i])
			mlx_destroy_image(img->attack[i], mlxptr);
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
		mlx_destroy_image(img->wall, mlxptr);
	if (img->exit)
		mlx_destroy_image(img->exit, mlxptr);
	if (img->floor)
		mlx_destroy_image(img->floor, mlxptr);
	while (++i < n_coin)
		if (img->coin[i])
			mlx_destroy_image(img->coin[i], mlxptr);
}
