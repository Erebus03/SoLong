/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:47 by araji             #+#    #+#             */
/*   Updated: 2025/02/05 02:31:09 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void    cleanup(t_game_info *game)
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
        close(game->fd);
    free(game);
}

int	check_args(int ac, char **av, t_game_info *game)
{
	if (ac != 2)
	{
		ft_printf("Valid args: %s <map file name>\n", av[0]);
		return (0);
	}
	if (ft_strncmp((av[1] + (ft_strlen(av[1]) - 4)), ".ber", 4) != 0)
	{
		ft_printf("Error: File must end with .ber\n");
		return (0);
	}
	if (av[1][0] == '.' && ft_strncmp(av[1], ".ber", 4) != 0)
	{
		ft_printf("Error: Hidden file not allowed\n");
		return (0);
	}
	game->fd = open(av[1], O_RDONLY);
	if (game->fd == -1)
	{
		perror("Error: Failed to open file");
		return (0);
	}
	return (1);
}

int	init_game(t_game_info *game, char *filename)
{
	game->var = malloc(sizeof(t_vars));
	if (!game->var)
    {
        ft_printf("Error: Memory allocation failed for vars\n");
        return (0);
    }
	game->grid = malloc(sizeof(t_map));
    if (!game->grid)
    {
        ft_printf("Error: Memory allocation failed for grid\n");
        free(game->var);
        game->var = NULL;
        return (0);
    }
    *(game->var) = (t_vars){{0, 0}, 0, 0, 0};
    *(game->grid) = (t_map){0, 0};
    game->map = make_map(game->fd, game->grid, filename);
    if (!game->map)
    {
        ft_printf("Error: Failed to create map\n");
        return (0);
    }
    if (!is_map_valid(game->map, game->grid, game->var, filename))
    {
        ft_printf("Error: Invalid ma\n");
        return (0);
    }
    return (1);
}

void	render_map(void)
{
	ft_printf("All good, get rendering..\n");
}

int	main(int ac, char **av)
{
	t_game_info	*ginfo;

	ginfo = malloc(sizeof(t_game_info));
    if (!ginfo)
    {
        ft_printf("Error: Memory allocation failed for game\n");
        return (1);
    }
    *ginfo = (t_game_info){NULL, NULL, NULL, -1};
	if (!check_args(ac, av, ginfo))
	{
		cleanup(ginfo);
		return (1);;
	}
	if(!init_game(ginfo, av[1]))
	{
		cleanup(ginfo);
		return (1);
	}
	render_map();
	cleanup(ginfo);
	return (0);
}
