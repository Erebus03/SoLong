/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:47 by araji             #+#    #+#             */
/*   Updated: 2025/02/04 06:32:52 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <fcntl.h>

/*
	check file name and all that
	check map and stuff
	start rendering
*/
int	check_file_name(char *filename)
{
	char	*ext;

	ext = ".ber";
	if (ft_strncmp((filename + (ft_strlen(filename) - 4)), ext, 4) != 0)
	{
		ft_printf("File is not .ber\n");
		return (0);
	}
	if (filename[0] == '.' && ft_strncmp(filename, ".ber", 4) != 0)
	{
		ft_printf("Hidden file\n");
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
	char	**map;
	t_vars	*var;
	t_map	*grid;
	int		fd;
	int		valid_map;

	if (ac != 2)
	{
		ft_printf("Valid args: %s <map file name>\n", av[0]);
		exit(1);
	}
	if (!check_file_name(av[1]))
		return (1);
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
	{
		printf("Map not valid!");
		free_map(map, grid->rows);
		free(grid);
		free(var);
		close(fd);
	}
	else
		render_map();
	return (0);
}
