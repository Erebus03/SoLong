#include "solong.h"

int count_lines_and_columns(int fd, int *rows, int *cols)
{
    char *line;
    *rows = 0;
    *cols = 0;

    while ((line = get_next_line(fd)) != NULL) {
        int line_len = strlen(line); //		make ft_strlen
        if (*rows == 0)
            *cols = line_len; // Set the initial column count
        else if (line_len != *cols) {// check if they're all the same
            free(line);
            return 0;
        }
        (*rows)++;
        free(line);
    }
    return (*rows > 0 && *cols > 0 && *rows != *cols); // Valid rectangle, but NOT A SQUARE(else : remove this part '*rows != *cols' )
}

char **allocate_map(int rows, int cols)
{
	int i;
    char **map;

	map = malloc(rows * sizeof(char *));
    if (!map) {
        perror("Failed to allocate memory for map rows");
        return NULL;
    }

	i = 0;
    while (i < rows)
	{
        map[i] = malloc((cols + 1) * sizeof(char)); // +1 for null terminator
        if (!map[i]) {
            perror("Failed to allocate memory for map columns");
            // Free previously allocated memory
            free_map(map, rows);
            return NULL;
        }
		i++;
    }

    return map;
}

void populate_map(int fd, char **map, int rows, int cols)
{
    char *line;
	int i;

	line = NULL;
	i = 0;

    while (i < rows)
	{
        line = get_next_line(fd);
        if (!line) {
            break; // Handle unexpected end of file
        }
        strncpy(map[i], line, cols);//							ft_strncpy
        map[i][cols] = '\0'; // Null-terminate the row
        free(line); // Free the line after copying
		i++;
    }
}

char **make_map(int fd, int *rows, int *cols)
{
	int fd2;

    // First pass: count rows and columns
    if (!count_lines_and_columns(fd, rows, cols)) {
        return (NULL);
    }

    // Allocate memory for the map
    char **map = allocate_map(*rows, *cols);
    if (!map) {
        return (NULL);
    }

    // Second pass: populate the map
	fd2 = open("map.ber", O_RDONLY);  //						file opening to close or change name
    populate_map(fd2, map, *rows, *cols);
	close(fd2);

    return (map);
}
