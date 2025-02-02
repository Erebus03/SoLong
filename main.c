/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:22:47 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 00:45:45 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int ac, const char **av)
{
	char	**map;
	t_vars	*var;
	char	*file_ext;
	int		rows;
	int		cols;
	int		fd;
	int		valid_map;

	if (ac != 2)
	{
		ft_printf("Valid args: %s <map file name>\n", av[0]);
		exit(1);
	}
	file_ext = ".ber";
	if (ft_strncmp(ft_substr(av[1], ft_strlen(av[1]) - 4, 4)
			, file_ext, 4) != 0)
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
	if (fd == -1) //	fd < 0
	{
		perror("Open() error");
		exit (1);
	}
	var = malloc(sizeof(t_vars));
	if (!var)
	{
		ft_printf("Memory allocation failed for variables");
		return (1); // exit with 1 or 0? , cuz its not rlly an err
	}
	map = make_map(fd, &rows, &cols);
	if (!map)
	{
		ft_printf("Failed to translate map.\n");
		close(fd);
		return (1);
	}
	ft_printf("map allocated and made.\n");
	ft_printf("Map (rows: %d, cols: %d):\n", rows, cols);
	for (int i = 0; i < rows; i++)
		ft_printf("%s\n", map[i]);
	ft_printf("checking the map now:\n");
	*var = (t_vars){{0, 0}, 0, 0, 0};
	valid_map = is_map_valid(map, rows, cols, var);
	ft_printf("is map valid >%d< (1 if valid)\n\n", valid_map);
	

	ft_printf("%p\n", map);
	ft_printf("in free_map\n");
	free_map(map, rows);

	ft_printf("%p\n", map);
	ft_printf("out\n");

	close(fd);

	return (0);
}
