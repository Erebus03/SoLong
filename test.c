#include <stdio.h>

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
}