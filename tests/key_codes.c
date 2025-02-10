# include "../../minilibx-linux/mlx.h"
# include "../solong.h"

typedef struct s_data {
    void *mlx;
    void *win;
} t_data;

int key_input(int keycode, void *param)
{
    write(1, "K", 1);  // Minimal output to verify hook works
    return (0);
}

int main() {
    t_data data;

    // Initialize MiniLibX
    data.mlx = mlx_init();
    if (!data.mlx) {
        printf("Error initializing MLX\n");
        return 1;
    }

    // Create a window
    data.win = mlx_new_window(data.mlx, 50, 50, "Example");
    if (!data.win) {
        printf("Error creating window\n");
        return 1;
    }

    // Set the key hook
    mlx_key_hook(data.win, key_input, &data);

    // Start the MLX loop
    mlx_loop(data.mlx);

    return 0;
}
