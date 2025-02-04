/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:47 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 21:41:04 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int ac, char **av)
{
	char	**map;
	t_vars	*var;
	t_map	*grid;
	char	*file_ext;
	int		fd;
	int		valid_map;

	if (ac != 2)
	{
		ft_printf("Valid args: %s <map file name>\n", av[0]);
		exit(1);
	}
	file_ext = ".ber";
	if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), file_ext, 4) != 0)
	{
		ft_printf("not .ber\n");
		return (1);
	}
	if (av[1][0] == '.' && ft_strncmp(av[1], ".ber", 4) != 0)
	{
		ft_printf("hidden file\n");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Open() error");
		exit (1);
	}
	var = malloc(sizeof(t_vars));
	grid = malloc(sizeof(t_map));
	if (!var || !grid)
	{
		ft_printf("Memory allocation failed for variables or grid!");
		free(var);
		free(grid);
		return (1);
	}
	*var = (t_vars){{0, 0}, 0, 0, 0};
	*grid = (t_map){0, 0};
	map = make_map(fd, grid, av[1]);
	if (!map)
	{
		ft_printf("Failed to translate map.\n");
		free(var);
		free(grid);
		close(fd);
		return (1);
	}
	printf("Map (rows: %d, cols: %d):\n", grid->rows, grid->cols);
	valid_map = is_map_valid(map, grid, var, av[1]);
	if (valid_map == 0)
		printf("Map not valid!");
	else
		printf("Start rendering..");
	free_map(map, grid->rows);
	free(grid);
	free(var);
	
	close(fd);
	return (0);
}
