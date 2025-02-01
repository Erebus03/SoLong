#include "solong.h"

int main(int ac, const char **av)
{
    int fd;
	vars *var;

	if (ac == 2)
	{
		char *file_ext = ".ber";
		if (ft_strncmp(ft_substr(av[1], ft_strlen(av[1]) - 4, 4), file_ext, 4) != 0)
		{
			printf("not .ber\n");
			return 1;
		}
		if (av[1][0] == '.' && ft_strncmp(av[1], ".ber", 4) != 0)
		{
			printf("hidden file\n");
			return 1;
		}
		fd = open(av[1], O_RDONLY);
		if (fd < 0) {
			perror("Failed to open map file");
			return 1;
		}

		int rows, cols;
		char **map;
		var = malloc(sizeof(vars));
		if (!var) {
			perror("Memory allocation failed for variables");
			return 0;
		}
		map = make_map(fd, &rows, &cols);
		if (!map) {
			fprintf(stderr, "Failed to translate map.\n");
			close(fd);
			return 1;
		}
		printf("map allocated and made, here it is:\n");
		printf("Map (rows: %d, cols: %d):\n", rows, cols);

		for (int i = 0; i < rows; i++) {
			printf("%s\n", map[i]);
		}

		printf("checking the map now:\n");
		*var = (vars){{0, 0}, 0, 0, 0};
		printf("is map valid >%d< (1 if valid)\n\n", is_map_valid(map, rows, cols, var));

		free_map(map, rows);
		close(fd);
	}
	else
		printf("valid args are  |> ./exe map_name.ber ");
    return 0;
}