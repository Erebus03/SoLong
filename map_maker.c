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

void	free_map(int rows, char **map)
{
	int	i;

	if (!map || !*map)
		return ;
	i = 0;
	while (i < rows)
	{
		if (map[i])
			free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

int	count_lines_and_columns(t_game *game)
{
	char	*line;
	int		line_len;

	game->rows = 0;
	game->cols = 0;
	game->fd = open(game->filename, O_RDONLY);
	line = get_next_line(game->fd);
	while (line != NULL)
	{
		line_len = ft_strlen(line);
		if (game->rows == 0)
			game->cols = line_len;
		else if (line_len != game->cols)
		{
			free(line);
			ft_printf("Error\nMap ain't rectangular!\n");
			return 0;
		}
		(game->rows)++;
		free(line);
		line = get_next_line(game->fd);
	}
	free(line);
	line = NULL;
	return (game->rows > 0 && game->cols > 0);
}

char	**allocate_map(t_game *game)
{
	int		i;

	game->map = malloc(game->rows * sizeof(char *));
	if (!game->map)
	{
		ft_printf("Error\nFailed to allocate memory for map rows");
		return (NULL);
	}
	i = 0;
	while (i < game->rows)
	{
		game->map[i] = malloc((game->cols + 1));
		if (!game->map[i])
		{
			ft_printf("Error\nFailed to allocate memory for map columns");
			free_map(game->rows, game->map);
			return (NULL);
		}
		i++;
	}
	return (game->map);
}

int	populate_map(t_game *game)
{
	char	*line;
	int		lines_read;
	int		i;

	line = NULL;
	lines_read = 0;
	i = 0;
	game->fd = open(game->filename, O_RDONLY);
	while (i < game->rows)
	{
		line = get_next_line(game->fd);
		if (!line)
			return (0);
		lines_read++;
		ft_strncpy(game->map[i], line, game->cols);
		if (!game->map[i])
			return (0);
		game->map[i][game->cols] = '\0';
		free(line);
		i++;
	}
	return (lines_read);
}

void	make_map(t_game *game)
{
	if (!count_lines_and_columns(game))
		cleanup(game, 1);
	game->map = allocate_map(game);//	Add error msgs
	if (!game->map)
		cleanup(game, 1);
	if (!populate_map(game))
		cleanup(game, 1);
}
