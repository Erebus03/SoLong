/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:47 by araji             #+#    #+#             */
/*   Updated: 2025/02/05 10:59:54 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	cleanup(t_game *game, int exitmode)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->rows, game->map);
	game->map = NULL;
	if (game->fd > 0)
		close(game->fd);
	if (game->imgs)
	{
		free_images(game->imgs, game->mlx);
		free(game->imgs);
	}
	game->imgs = NULL;
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free(game);
	game = NULL;
	exit(exitmode);
}

int	check_args(int ac, char **av, t_game *game)
{
	if (ac != 2)
	{
		ft_printf("Error\nValid args: %s <map file name>\n", av[0]);
		return (0);
	}
	if (ft_strncmp((av[1] + (ft_strlen(av[1]) - 4)), ".ber", 4) != 0)
	{
		ft_printf("Error\nFile must end with .ber\n");
		return (0);
	}
	if (av[1][0] == '.' && av[1][1] != '.' &&
		av[1][0] != '/' && ft_strncmp(av[1], ".ber", 4) != 0) //	remove ../ 
	{
		ft_printf("Error\nHidden file not allowed\n");
		return (0);
	}
	game->fd = open(av[1], O_RDONLY);
	if (game->fd == -1)
	{
		perror("Error\nFailed to open file");
		return (0);
	}
	return (1);
}

int	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	make_map(game);
	if (!game->map)
	{
		ft_printf("Error\nFailed to create map\n");
		cleanup(game, 1);
	}
	if (!is_map_valid(game))
		cleanup(game, 1);
	return (1);
}

int	render_map(t_game *game, t_paths *paths)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		printf("mlx_init failed\n");
	if (!win_init(game, &paths))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	*ginfo;
	t_paths	paths;

	ginfo = malloc(sizeof(t_game));
	if (!ginfo)
	{
		ft_printf("Error\nMemory allocation failed for game\n");
		return (1);
	}
	*ginfo = (t_game){0, 0, {0, 0}, 0, 0, 0, 0,
		NULL, NULL, NULL, -1, NULL, NULL, 0};
	if (!check_args(ac, av, ginfo))
		cleanup(ginfo, 1);
	ginfo->filename = av[1];
	init_game(ginfo);
	render_map(ginfo, &paths);
	mlx_key_hook(ginfo->win, key_input, ginfo);
	mlx_loop_hook(ginfo->mlx, loop_init, ginfo);
	mlx_loop(ginfo->mlx);
	cleanup(ginfo, 0);
	return (0);
}
