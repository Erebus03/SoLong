#include "solong.h"
#include <stdio.h>
#include <stdlib.h>
#define UP 65362
#define DOWN 65364
#define RIGHT 65363
#define LEFT 65361
#define CLOSE 65307

char	*display_score(t_game *game) //free
{
	char	*msg;

	msg = ft_strjoin("Moves: ", ft_itoa(game->moves));
	msg = ft_strjoin(msg, " With ");
	msg = ft_strjoin(msg, ft_itoa(game->collected));
	msg = ft_strjoin(msg, "/");
	msg = ft_strjoin(msg, ft_itoa(game->coin));
	msg = ft_strjoin(msg, " Eaten");
	return (msg);
}

// int main()
// {
// 	t_game game;
// 	char *msg;
// 	game.mlx = NULL;
// 	game.win = NULL;
// 	game.mlx = mlx_init();
// 	game.win = mlx_new_window(game.mlx, (game.cols * 50),
// 		(game.rows * 50), "test");
// 	game.moves = 10000;
// 	game.collected = 21;
// 	game.coin = 42;
// 	msg = display_score(&game);
// 	printf("%s\n", msg);
// 	free(msg);
// 	mlx_loop_hook(game.mlx, loop_init, &game);
// 	mlx_loop(game.mlx);
// 	return 0;
// }


int loop_init(t_game *game)
{
	char *score;
    
    score = display_score(game);
    mlx_string_put(game->mlx, game->win, 10, 20, 0x00FFFFFF, score);
    free(score);
    
    return (0);
}
int key_input(int key, t_game *game)
{
	if (key == UP ||key == LEFT ||key == RIGHT ||key == DOWN)
		game->coin++;
	return (0);
}

int main()
{
    t_game game;
    char *msg;
    
    // Initialize game structure
    game.mlx = NULL;
    game.win = NULL;
    game.rows = 10;
    game.cols = 15;
    
    // Initialize MLX
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, (game.cols * 50),
        (game.rows * 50), "test");
    
    // Set game values
    game.moves = 10000;
    game.collected = 21;
    game.coin = 42;
    
    // Test display_score function
    msg = display_score(&game);
    printf("%s\n", msg);
    free(msg);
	
    
    // Set up MLX hooks and loop
	mlx_key_hook(game.win, key_input, &game);
    mlx_loop_hook(game.mlx, loop_init, &game);
    mlx_loop(game.mlx);
    
    return 0;
}