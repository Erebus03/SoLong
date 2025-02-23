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

int	cleanup(t_game *game, int exitmode)
{
	if (!game)
		return (0);
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

int	check_args(int ac, char **av)
{
	char	*file;
	if (ac != 2)
	{
		ft_printf("Error\nValid args: %s <map file name>\n", av[0]);
		return (0);
	}
	if (ft_strncmp((av[1] + (ft_strlen(av[1]) - 4)), ".ber", 4) == 0)
	{
		file = ft_strrchr(av[1], '/') + 1;
		if (file[0] == '.')
		{
			ft_printf("Error\nHidden file not allowed\n");
			return (0);
		}
	}
	else
	{
		ft_printf("Error\nFile must end with .ber\n");
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
	{
		ft_printf("Error\nMap ain't valid\n");
		cleanup(game, 1);
	}	return (1);
}

int	render_map(t_game *game, t_paths *paths)
{
	int (i), (j);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error\nFunction mlx_init() failed\n");
		cleanup(game, 1);
	}
	if (!win_init(game, &paths))
	{
		ft_printf("Error\nFailed to initialize window\n");
		cleanup(game, 1);
	}
	i = -1;
	while (++i < game->rows)
	{
		j = -1;
		while (++j < game->cols)
		{
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->imgs->wall,
					j * 50, i * 50);
		}
	}
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
	*ginfo = (t_game){-1, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0},
		0, 0, -1, -1, -1, 0, 0, 0, NULL, NULL, NULL, NULL, NULL};
	if (!check_args(ac, av))
		cleanup(ginfo, 1);
	ginfo->filename = av[1];
	init_game(ginfo);
	render_map(ginfo, &paths);
	mlx_key_hook(ginfo->win, key_input, ginfo);
	mlx_loop_hook(ginfo->mlx, loop_init, ginfo);
	mlx_hook(ginfo->win, 17, 0, cleanup, ginfo);
	mlx_loop(ginfo->mlx);
	cleanup(ginfo, 0);
	return (0);
}
