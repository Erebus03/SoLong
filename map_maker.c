#include "solong.h"

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