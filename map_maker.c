/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:35 by araji             #+#    #+#             */
/*   Updated: 2025/02/05 02:46:01 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	free_map(char **map, int rows)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
}

int	count_lines_and_columns(int fd, t_map *grid)
{
	char	*line;
	int		line_len;

	grid->rows = 0;
	grid->cols = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_len = ft_strlen(line);
		if (grid->rows == 0)
			grid->cols = line_len;
		else if (line_len != grid->cols)
		{
			free(line);
			ft_printf("Error\nMap ain't rectangular!\n");
			return (0);
		}
		(grid->rows)++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (grid->rows > 0 && grid->cols > 0);
}

char	**allocate_map(int rows, int cols)
{
	int		i;
	char	**map;

	map = malloc(rows * sizeof(char *));
	if (!map)
	{
		ft_printf("Error\nFailed to allocate memory for map rows");
		return (NULL);
	}
	i = 0;
	while (i < rows)
	{
		map[i] = malloc((cols + 1) * sizeof(char));
		if (!map[i])
		{
			ft_printf("Error\nFailed to allocate memory for map columns");
			free_map(map, rows);
			return (NULL);
		}
		i++;
	}
	return (map);
}

int	populate_map(int fd, char **map, int rows, int cols)
{
	char	*line;
	int		lines_read;
	int		i;

	line = NULL;
	lines_read = 0;
	i = 0;
	while (i < rows)
	{
		line = get_next_line(fd);
		if (!line)
		{
			ft_printf("Error\nCoudn't read line in populate_map()\n");
			break ;
		}
		lines_read++;
		ft_strncpy(map[i], line, cols);
		map[i][cols] = '\0';
		free(line);
		i++;
	}
	return (lines_read);
}

char	**make_map(int fd, t_map *grid, char *filename)
{
	int		fd2;
	char	**map;

	if (!count_lines_and_columns(fd, grid))
		return (NULL);
	map = allocate_map(grid->rows, grid->cols);
	if (!map)
		return (NULL);
	fd2 = open(filename, O_RDONLY);
	if (populate_map(fd2, map, grid->rows, grid->cols) != grid->rows)
		return (NULL);
	close(fd2);
	return (map);
}
