#include "solong.h"

// Function to validate the map
int is_map_valid(char **map, int rows, int cols, vars *variables) //there are more than 25 lines!!
{
    char cell;
    int i;
    int j;

    i = 0;
    while (i < rows) // Check each cell in the map
    {
        j = 0;
        while (j < cols)
		{
            cell = map[i][j];
            update_stats(cell, i, j, variables);
            j++;
        }
        i++;
    }
    if (check_boundries(rows, cols, map) == 0 || error_handling(variables) == 0) // Validate player, exit, and collectible counts
        return 0;
	if (all_is_reachable(variables->p_pos[0], variables->p_pos[1], rows, cols) == 0)
	{
		printf("exit/coin aint reachable!\n");
	}
    return 1; // Map is valid
}

int check_boundries(int rows, int cols, char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < rows) // Check each cell in the map
    {
        j = 0;
        while (j < cols)
		{
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
            {
                if ( map[i][j] != '1')
                {	
                    printf("Error: Map is not surrounded by walls at (%d, %d)\n", i, j);
                    return 0;
                }
            }
            j++;
        }
        i++;
    }
    return (1);
}

void    update_stats(char cell, int i, int j, vars *variables)
{
    if (cell == 'P')
    {
        variables->player++;
        variables->p_pos[0] = j; // cols
        variables->p_pos[1] = i; // rows
        printf("player pos (%d,%d)\n",variables->p_pos[0], variables->p_pos[1] );
    }
    else if (cell == 'E')
        variables->exit++;
    else if (cell == 'C')
        variables->coin++;
}

int    error_handling(vars *variables)
{
    if (variables->player != 1) {
        printf("Error: Map must contain exactly one player (P). Found: %d\n", variables->player);
        return 0;
    }
    if (variables->exit != 1) {
        printf("Error: Map must contain exactly one exit (E). Found: %d\n", variables->exit);
        return 0;
    }
    if (variables->coin < 1) {
        printf("Error: Map must contain at least one collectible (C). Found: %d\n", variables->coin);
        return 0;
    }
    return 1;
}

// Function to free the 2D array
void free_map(char **map, int rows)
{
    int i = 0;
    while (i < rows)
        free(map[i++]);
    free(map);
}



int main()
{
    int fd;
	vars *var;

    fd = open("map.ber", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open map file");
        return 1;
    }

    int rows, cols;
    char **map;
	var = malloc(sizeof(vars));
	if (!var) {
		perror("Memory allocation failed for variables");
		return 0; // Handle error appropriately
	}
	*var = (vars){{0, 0}, 0, 0, 0};
    map = make_map(fd, &rows, &cols);
    if (!map) {
        fprintf(stderr, "Failed to translate map.\n");
        close(fd);
        return 1;
    }

    printf("Map (rows: %d, cols: %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        printf("%s\n", map[i]); // Print each row as a string
    }

    printf("is map valid >%d< (1 if valid)\n\n", is_map_valid(map, rows, cols, var));

    free_map(map, rows);
    close(fd);
    return 0;
}

/*

*/



/*
char **make_map(int fd, int *rows, int *cols)
{
    char *line = NULL;
    *rows = 0;
    *cols = 0;

    // Temporary storage for lines
    char **temp_map = NULL;
    int temp_capacity = 0;

    // First pass: read all lines and store them temporarily
    while ((line = get_next_line(fd)) != NULL) {
        // Dynamically grow the temporary map storage
        if (*rows >= temp_capacity) {
            temp_capacity = (*rows == 0) ? 1 : temp_capacity * 2;
            temp_map = realloc(temp_map, temp_capacity * sizeof(char *));
            if (!temp_map) {
                perror("Failed to allocate memory for temporary map");
                return NULL;
            }
        }

        // Store the line in the temporary map
        temp_map[*rows] = line;
        (*rows)++;

        // Determine columns based on the first line
        if (*cols == 0) {
            *cols = strlen(line);
        }
    }

    // Allocate memory for the 2D array
    char **map = malloc(*rows * sizeof(char *));
    if (!map) {
        perror("Failed to allocate memory for map rows");
        // Free temporary map storage
        for (int i = 0; i < *rows; i++) {
            free(temp_map[i]);
        }
        free(temp_map);
        return NULL;
    }

    // Copy lines from temporary storage to the 2D array
    for (int i = 0; i < *rows; i++) {
        map[i] = malloc((*cols + 1) * sizeof(char)); // +1 for null terminator
        if (!map[i]) {
            perror("Failed to allocate memory for map columns");
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(map[j]);
            }
            free(map);
            // Free temporary map storage
            for (int j = 0; j < *rows; j++) {
                free(temp_map[j]);
            }
            free(temp_map);
            return NULL;
        }
        strncpy(map[i], temp_map[i], *cols); // Copy the line into the 2D array
        map[i][*cols] = '\0'; // Null-terminate the row
        free(temp_map[i]); // Free the temporary line
    }

    // Free the temporary map storage
    free(temp_map);

    return map;
}
*/

// Function to translate a map file to a 2D array
/*
char **make_map(int fd, int *rows, int *cols)
{
    char *line = NULL;
    *rows = 0;
    *cols = 0;

    // First pass: count rows and determine columns
    while ((line = get_next_line(fd)) != NULL) {
        if (*cols == 0) {
            *cols = strlen(line); // Determine columns based on the first line
        }
        (*rows)++;
        free(line); // Free the line after processing
    }

    // Reset the file pointer to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // Allocate memory for the 2D array
    char **map = malloc(*rows * sizeof(char *));
    if (!map) {
        perror("Failed to allocate memory for map rows");
        return NULL;
    }

    for (int i = 0; i < *rows; i++) {
        map[i] = malloc((*cols + 1) * sizeof(char)); // +1 for null terminator
        if (!map[i]) {
            perror("Failed to allocate memory for map columns");
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(map[j]);
            }
            free(map);
            return NULL;
        }
    }

    // Second pass: fill the 2D array with the map data
    int row = 0;
    while ((line = get_next_line(fd)) != NULL) {
        strncpy(map[row], line, *cols); // Copy the line into the 2D array
        map[row][*cols] = '\0'; // Null-terminate the row
        row++;
        free(line); // Free the line after processing
    }

    return map;
}
*/