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

	//ask if a empty map is valid to work on or should it throw an error
    return (*rows > 0 && *cols > 0 && *rows != *cols); // Valid rectangle, but NOT A SQUARE(else : remove this part '*rows != *cols' )
}

static char **allocate_map(int rows, int cols)
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

static void populate_map(int fd, char **map, int rows, int cols)
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





/*
void    print_map(char map[5][11])
{
    int i;

    i = 0;
    while (i < 5)
    {
        printf("%s\n", map[i]);
        i++;
    }
}

void    flood_fill(char map[5][11], int x, int y)
{
    if (x < 0 || x >= 10 || y < 0 || y >= 5)
        return ;
    if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'C' || map[y][x] == 'E')
        return ;

    map[y][x] = 'V';
    
    flood_fill(map, x - 1, y);
    flood_fill(map, x + 1, y);
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
}

int main(void)
{
    char map[5][11] = {
        "1111111111",
        "1010000001",
        "101PCC0E01",
        "1000000001",
        "1111111111"
    };

    printf("Before:\n");
    print_map(map);

    flood_fill(map, 3, 3);
    printf("\nAfter:\n");
    print_map(map);

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (map[y][x] == '0')
            {
                printf("something aint reachable!\n");
                return 1;
            }
        }
    }
    printf("all items are reachable!\n");
    return (0);
}*/