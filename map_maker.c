/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:35 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 00:48:25 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	count_lines_and_columns(int fd, int *rows, int *cols)
{
	char	*line;
	int		line_len;

	*rows = 0;
	*cols = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_len = ft_strlen(line); // make it ft_strlen
		if (*rows == 0)
			*cols = line_len;
		else if (line_len != *cols)
		{
			free(line);
			return (0);
		}
		(*rows)++;
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("\n\nr%d c%d\n\n", *rows, *cols);
	// Valid rectangle, but NOT A SQUARE(else
	//remove this part '*rows != *cols' )
	return (*rows > 0 && *cols > 0 && *rows != *cols);
}

char	**allocate_map(int rows, int cols)
{
	int		i;
	char	**map;

	map = malloc(rows * sizeof(char *));
	if (!map)
	{
		perror("Failed to allocate memory for map rows");
		return (NULL);
	}
	i = 0;
	while (i < rows)
	{
		map[i] = malloc((cols + 1) * sizeof(char));
		if (!map[i])
		{
			perror("Failed to allocate memory for map columns");
			free_map(map, rows);
			return (NULL);
		}
		i++;
	}
	return (map);
}

void	populate_map(int fd, char **map, int rows, int cols)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (i < rows)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_strncpy(map[i], line, cols);//					make ft_strncpy
		map[i][cols] = '\0';
		free(line);
		i++;
	}
}

char	**make_map(int fd, int *rows, int *cols)
{
	int		fd2;
	char	**map;

	if (!count_lines_and_columns(fd, rows, cols))
		return (NULL);
	map = allocate_map(*rows, *cols);
	if (!map)
		return (NULL);
	fd2 = open("map.ber", O_RDONLY);// find a solution to opening this shit
	populate_map(fd2, map, *rows, *cols);
	close(fd2);
	return (map);
}
