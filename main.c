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

void	cleanup(t_game_info *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->map, game->grid->rows);
	if (game->grid)
		free(game->grid);
	if (game->var)
		free(game->var);
	if (game->fd > 0)
	{
		close(game->fd);
	}
	if (game->imgs)
		free_images(game->imgs, game->mlx);
	if (game->imgs)
		free(game->imgs);
	if (game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}

int	check_args(int ac, char **av, t_game_info *game)
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
	if (av[1][0] == '.' && ft_strncmp(av[1], ".ber", 4) != 0)
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

int	init_game(t_game_info *game, char *filename)
{
	game->var = malloc(sizeof(t_vars));
	game->grid = malloc(sizeof(t_map));
	game->mlx = malloc(sizeof(void *));	
	game->win = malloc(sizeof(void *));	
	if (!game->var || !game->grid || !game->mlx || !game->win)
	{
		ft_printf("Error\nMemory allocation failed for init_game()\n");
		cleanup(game);
		exit (1);
	}
	*(game->var) = (t_vars){{0, 0}, 0, 0, 0, 0};
	*(game->grid) = (t_map){0, 0};
	game->map = make_map(game->fd, game->grid, filename);
	if (!game->map)
	{
		ft_printf("Error\nFailed to create map\n");
		return (0);
	}
	if (!is_map_valid(game->map, game->grid, game->var, filename))
	{
		ft_printf("Error\nInvalid ma\n");
		return (0);
	}
	return (1);
}

int	render_map(t_game_info *game, t_paths *paths)
{
	game->mlx = mlx_init();
	if (!win_init(game, &paths))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game_info	*ginfo;
	t_paths		paths;

	ginfo = malloc(sizeof(t_game_info));
	if (!ginfo)
	{
		ft_printf("Error\nMemory allocation failed for game\n");
		return (1);
	}
	*ginfo = (t_game_info){NULL, NULL, NULL, NULL, -1, NULL, NULL, 0, 0};
	if (!check_args(ac, av, ginfo))
	{
		cleanup(ginfo);
		return (1);
	}
	if (!init_game(ginfo, av[1]))
	{
		cleanup(ginfo);
		return (1);
	}
	render_map(ginfo, &paths);
	mlx_loop(ginfo->mlx);
	cleanup(ginfo);
	return (0);
}
