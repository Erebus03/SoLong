#include "solong.h"
#include <unistd.h>
#include <stdlib.h>

char **read_lines_to_temp(int fd, int *rows, int *cols)
{
    char **temp_map = NULL;
    int temp_capacity = 1;
    *rows = 0;
    *cols = 0;

    // Read all lines from the file
    while (1) {
        char *line = get_next_line(fd);
        if (!line)
            break;

        // Dynamically grow the temporary map storage
        if (*rows >= temp_capacity) {
            temp_capacity *= 2;
            char **new_temp_map = malloc(temp_capacity * sizeof(char *));
            if (!new_temp_map) {
                perror("Failed to allocate memory for temporary map");
                free(line);
                for (int i = 0; i < *rows; i++) {
                    free(temp_map[i]);
                }
                free(temp_map);
                return NULL;
            }

            // Copy existing lines to the new buffer
            for (int i = 0; i < *rows; i++) {
                new_temp_map[i] = temp_map[i];
            }

            // Free the old temporary map and update the pointer
            free(temp_map);
            temp_map = new_temp_map;
        }

        // Store the line in the temporary map
        temp_map[*rows] = line;
        (*rows)++;

        // Determine columns based on the first line
        if (*cols == 0) {
            for (*cols = 0; line[*cols] != '\0' && line[*cols] != '\n'; (*cols)++);
        }
    }

    return temp_map;
}

char **allocate_2d_array(int rows, int cols)
{
    char **map = malloc(rows * sizeof(char *));
    if (!map) {
        perror("Failed to allocate memory for map rows");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        map[i] = malloc((cols + 1) * sizeof(char)); // +1 for null terminator
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

    return map;
}

void copy_lines_to_2d_array(char **map, char **temp_map, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            map[i][j] = temp_map[i][j]; // Copy each character
        }
        map[i][cols] = '\0'; // Null-terminate the row
        free(temp_map[i]); // Free the temporary line
    }
}

char **translate_map_to_2d_array(int fd, int *rows, int *cols)
{
    // Read lines into temporary storage
    char **temp_map = read_lines_to_temp(fd, rows, cols);
    if (!temp_map) {
        return NULL;
    }

    // Allocate memory for the 2D array
    char **map = allocate_2d_array(*rows, *cols);
    if (!map) {
        // Free temporary map storage
        for (int i = 0; i < *rows; i++) {
            free(temp_map[i]);
        }
        free(temp_map);
        return NULL;
    }

    // Copy lines to the 2D array
    copy_lines_to_2d_array(map, temp_map, *rows, *cols);

    // Free the temporary map storage
    free(temp_map);

    return map;
}