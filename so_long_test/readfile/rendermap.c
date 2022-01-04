#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#define WALL "./img/wall.xpm"
#define FLOOR "./img/dirt.xpm"

# define TILE_SIZE 32 //tamanho de cada "quadrado" em nossa malha/grid
# define PLAYER_TILE_SIZE 15 //tamanho do jogador (o quanto ele ocupa no quadrado)
# define MAP_NUM_ROWS 11 //total de linhas
# define MAP_NUM_COLS 15 //total de colunas
# define WINDOW_WIDTH MAP_NUM_COLS*TILE_SIZE //largura da janela
# define WINDOW_HEIGHT MAP_NUM_ROWS*TILE_SIZE //altura da janela

#define KEY_ESC 65307

int grid[MAP_NUM_ROWS][MAP_NUM_COLS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct s_game
{
	void *mlx;
	void *win;
	void *wall;
	void *floor;
	int wall_w;
	int wall_h;
	int floor_w;
	int floor_h;
} t_game;

void init_img(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx 42");
	game->wall = mlx_xpm_file_to_image(game->mlx, WALL, &game->wall_w, &game->wall_h);
	game->floor = mlx_xpm_file_to_image(game->mlx, FLOOR, &game->floor_w, &game->floor_h);
}

int key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(game->mlx, game->wall);
		mlx_destroy_image(game->mlx, game->floor);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}

	return (0);
}

void put_img(int x, int y, t_game *game, void *img)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x, y);
}

void print_map(t_game *game)
{
	int x, y;

	x = 0;
	y = 0;

	while (y < MAP_NUM_ROWS)
	{
		while (x < MAP_NUM_COLS)
		{
			if (grid[y][x] == 1)
				put_img(x * TILE_SIZE, y * TILE_SIZE, game, game->wall);
			else
				put_img(x * TILE_SIZE, y * TILE_SIZE, game, game->floor);
			x++;
		}
		x = 0;
		y++;
	}
}

int main()
{
	t_game game;

	init_img(&game);
	print_map(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);

	// mlx_destroy_display(game.mlx);
	// free(game.mlx);

	return (0);
}