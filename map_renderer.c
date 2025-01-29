/* Comprehensive MinilibX Map Renderer */
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define TILE_SIZE 64
#define MAX_MAP_WIDTH 20
#define MAX_MAP_HEIGHT 20

typedef struct s_game {
    void *mlx;
    void *win;
    char map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
    int map_width;
    int map_height;
    int player_x;
    int player_y;
    int coins_collected;
    int total_coins;
    void *wall_img;
    void *floor_img;
    void *player_img;
    void *coin_img;
    void *exit_img;
} t_game;

// Function prototypes
int read_map(t_game *game, const char *filename);
void render_map(t_game *game);
int handle_keypress(int keycode, t_game *game);
void init_game(t_game *game);
void load_images(t_game *game);

// Read map from file
int read_map(t_game *game, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open map file\n");
        return 0;
    }

    game->map_height = 0;
    game->map_width = 0;
    game->coins_collected = 0;
    game->total_coins = 0;

    char line[MAX_MAP_WIDTH + 2];
    while (fgets(line, sizeof(line), file) && game->map_height < MAX_MAP_HEIGHT) {
        int len = 0;
        while (line[len] && line[len] != '\n') {
            game->map[game->map_height][len] = line[len];
            
            // Find player, coins, track map dimensions
            if (line[len] == 'p') {
                game->player_x = len;
                game->player_y = game->map_height;
            } else if (line[len] == 'c') {
                game->total_coins++;
            }
            
            len++;
        }
        game->map[game->map_height][len] = '\0';
        
        // Update map width
        if (len > game->map_width) {
            game->map_width = len;
        }
        
        game->map_height++;
    }
    
    fclose(file);
    return 1;
}

// Render individual tile
void render_tile(t_game *game, int x, int y) {
    int screen_x = x * TILE_SIZE;
    int screen_y = y * TILE_SIZE;
    void *img = NULL;

    switch(game->map[y][x]) {
        case '1': img = game->wall_img; break;
        case '0': img = game->floor_img; break;
        case 'p': img = game->player_img; break;
        case 'c': img = game->coin_img; break;
        case 'e': img = game->exit_img; break;
        default: return;
    }

    if (img) {
        mlx_put_image_to_window(game->mlx, game->win, img, screen_x, screen_y);
    }
}

// Render entire map
void render_map(t_game *game) {
    // Clear window
    mlx_clear_window(game->mlx, game->win);

    // Render each tile
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            render_tile(game, x, y);
        }
    }
}

// Handle key presses for player movement
int handle_keypress(int keycode, t_game *game) {
    int new_x = game->player_x;
    int new_y = game->player_y;

    // Determine new position based on key
    switch (keycode) {
        case 119: // W key
        case 65362: // Up arrow
            new_y--;
            break;
        case 115: // S key
        case 65364: // Down arrow
            new_y++;
            break;
        case 97: // A key
        case 65361: // Left arrow
            new_x--;
            break;
        case 100: // D key
        case 65363: // Right arrow
            new_x++;
            break;
        case 65307: // Escape key
            exit(0);
    }

    // Check if new position is valid
    if (new_x >= 0 && new_x < game->map_width && 
        new_y >= 0 && new_y < game->map_height) {
        
        // Check for wall collision
        if (game->map[new_y][new_x] != '1') {
            // Remove player from old position
            game->map[game->player_y][game->player_x] = '0';
            
            // Check for coin collection
            if (game->map[new_y][new_x] == 'c') {
                game->coins_collected++;
            }
            
            // Move player
            game->player_x = new_x;
            game->player_y = new_y;
            game->map[new_y][new_x] = 'p';
            
            // Check for exit
            if (game->coins_collected == game->total_coins && 
                game->map[new_y][new_x] == 'e') {
                printf("Congratulations! You won!\n");
                exit(0);
            }
            
            // Re-render map
            render_map(game);
        }
    }

    return 0;
}

// Load game images
void load_images(t_game *game) {
    int width, height;

    // Load images (replace with your actual image paths)
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "./wall.xpm", &width, &height);
    game->floor_img = mlx_xpm_file_to_image(game->mlx, "./floor.xpm", &width, &height);
    game->player_img = mlx_xpm_file_to_image(game->mlx, "./player.xpm", &width, &height);
    game->coin_img = mlx_xpm_file_to_image(game->mlx, "./coin.xpm", &width, &height);
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "./exit.xpm", &width, &height);

    // Error checking
    if (!game->wall_img || !game->floor_img || !game->player_img || 
        !game->coin_img || !game->exit_img) {
        printf("Error loading images!\n");
        exit(1);
    }
}

// Initialize game
void init_game(t_game *game) {
    // Initialize MLX
    game->mlx = mlx_init();
    if (!game->mlx) {
        printf("Error initializing MLX\n");
        exit(1);
    }

    // Create window based on map size
    game->win = mlx_new_window(game->mlx, 
                                game->map_width * TILE_SIZE, 
                                game->map_height * TILE_SIZE, 
                                "Map Renderer");

    // Load images
    load_images(game);
}

int main(int argc, char **argv) {
    t_game game = {0};

    // Check argument
    if (argc != 2) {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    // Read map
    if (!read_map(&game, argv[1])) {
        return 1;
    }

    // Initialize game
    init_game(&game);

    // Initial render
    render_map(&game);

    // Set up event hooks
    mlx_key_hook(game.win, handle_keypress, &game);
    mlx_loop(game.mlx);

    return 0;
}
