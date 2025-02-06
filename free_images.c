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

void	free_player(t_img *img)
{
	int	i;
	int	n_pics;

	i = 0;
	n_pics = 2;
	while (i < n_pics)
		if (img->p_up[i])
			free(img->p_up[i]);
	i = 0;
	while (i < n_pics)
		if (img->p_down[i])
			free(img->p_down[i]);
	i = 0;
	while (i < n_pics)
		if (img->p_right[i])
			free(img->p_right[i]);
	i = 0;
	while (i < n_pics)
		if (img->p_left[i])
			free(img->p_left[i]);
}

void	free_enemy_attack(t_img *img)
{
	int	i;
	int	enemy_pics;
	int	attack_pics;

	i = 0;
	attack_pics = 2;
	enemy_pics = 4;
	while (i < enemy_pics)
		if (img->enemy[i])
			free(img->enemy[i]);
	i = 0;
	while (i < attack_pics)
		if (img->attack[i])
			free(img->attack[i]);
}

void	free_c_w_f_e(t_img *img)
{
	int	i;
	int	n_coin;

	i = 0;
	n_coin = 2;
	if (img->wall)
		free(img->wall);
	if (img->exit)
		free(img->exit);
	if (img->floor)
		free(img->floor);
	while (i < n_coin)
		if (img->coin[i])
			free(img->coin[i]);
}
