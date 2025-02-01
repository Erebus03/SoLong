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
	int		fd;
	t_vars	*var;
	char	*filename;
	char	*file_ext;
	int		rows;
	int		cols;
	char	**map;

	if (ac == 2)
	{
		file_ext = ".ber";
		if (ft_strncmp(ft_substr(av[1], ft_strlen(av[1]) - 4, 4)
				, file_ext, 4) != 0)
		{
			printf("not .ber\n");
			return (1);
		}
		if (av[1][0] == '.' && ft_strncmp(av[1], ".ber", 4) != 0)
		{
			printf("hidden file\n");
			return (1);
		}
		filename = av[1];
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Failed to open map file");
			return (1);
		}
		var = malloc(sizeof(t_vars));
		if (!var)
		{
			perror("Memory allocation failed for variables");
			return (0);
		}
		map = make_map(fd, filename, &rows, &cols);
		if (!map)
		{
			fprintf(stderr, "Failed to translate map.\n");
			close(fd);
			return (1);
		}
		printf("map allocated and made, here it is:\n");
		printf("Map (rows: %d, cols: %d):\n", rows, cols);
		for (int i = 0; i < rows; i++)
		{
			printf("%s\n", map[i]);
		}
		printf("checking the map now:\n");
		*var = (t_vars){{0, 0}, 0, 0, 0};
		printf("is map valid >%d< (1 if valid)\n\n",
			is_map_valid(map, rows, cols, var));
		free_map(map, rows);
		close(fd);
	}
	else
		printf("valid args are  |> ./exe map_name.ber ");
	return (0);
}
