#include "solong.h"

// Function to validate the map
int is_map_valid(char **map, int rows, int cols, vars *variables) //there are more than 25 lines!!
{
    char cell;
    int i;
    int j;

    i = 0;
	if (check_boundries(rows, cols, map) == 0)
		return 0;
    while (i < rows) // Check each cell in the map
    {
        j = 0;
        while (j < cols)
		{
            cell = map[i][j];
			if (cell == 'C' || cell == 'E' || cell == 'P')
            	update_stats(cell, i, j, variables);
            j++;
        }
        i++;
    }

    if (error_handling(variables) == 0) // Validate player, exit, and collectible counts
	{
        return 0;
	}
	if (all_is_reachable(variables->p_pos[0], variables->p_pos[1], rows, cols) == 0)
	{
		free_map(map, rows);
		printf("exit/coin aint reachable!\n");
		return 0;
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
