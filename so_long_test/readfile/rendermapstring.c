#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#define WALL "./img/wall.xpm"
#define FLOOR "./img/dirt.xpm"

#define COLLECTIBLE_CHAR 'C'
#define EXIT_CHAR 'E'
#define PLAYER_CHAR 'P'


# define TILE_SIZE 32 //tamanho de cada "quadrado" em nossa malha/grid
# define PLAYER_TILE_SIZE 15 //tamanho do jogador (o quanto ele ocupa no quadrado)


#define KEY_ESC 65307

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
	int		coins;
} t_player;


typedef struct s_game
{
	void *mlx;
	void *win;
	void *wall;
	void *floor;
	char	**map;
	int		map_num_rows;
	int		map_num_cols;
	int wall_w;
	int wall_h;
	int floor_w;
	int floor_h;
	t_player	player;
	int collectibles;
	int start_position;
	int exit;
	int	finish;
} t_game;

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void find_img_size(t_game *game)
{
	size_t x;

	x = 0;
	while (game->map[x])
		x++;
	game->map_num_rows = x * TILE_SIZE;
	game->map_num_cols = (ft_strlen(game->map[0])) * TILE_SIZE;
}

int ext_validator(char *path)
{
	int length;

	length = ft_strlen(path);
	if (ft_strcmp(path + length - 4, ".ber") != 0)
	{
		printf("Error\nInvalid file extension\n");
		return (0);
	}
	return (1);
}

int wall_validator(t_game *game)
{
	int x;
	int y;
	int rows;
	int colums;

	x = 0;
	y = 0;
	find_img_size(game);
	rows = (game->map_num_rows / TILE_SIZE) - 1;
	colums = (game->map_num_cols / TILE_SIZE) - 1;
	while(game->map[0][y] == '1' && game->map[rows][y] == '1' && y <= colums)
		y++;
	while(game->map[x][0] == '1' && game->map[x][colums] == '1' && x < rows)
		x++;
	if (--y != colums || x != rows)
	{
		printf("Error\nMap must be surrounded by walls\n");
		return (0);
	}
	return (1);
}

void map_init(t_game *game)
{
	game->player.coins = 0;
	game->collectibles = 0;
	game->start_position = 0;
	game->exit = 0;
	game->finish = 0;
}

int	map_validator(t_game *game)
{
	map_init(game);
	wall_validator(game);

	int x;
	int y;

	x = 0;
	y = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == PLAYER_CHAR)
				game->start_position++;
			if (game->map[x][y] == EXIT_CHAR)
				game->exit++;
			if (game->map[x][y] == COLLECTIBLE_CHAR)
				game->collectibles++;
			y++;
		}
		x++;
	}

	if (game->start_position != 1 || game->exit != 1 || game->collectibles < 1)
	{
		printf("Error\nMap must have exactly one player, one exit and at least one collectible\n");
		return (0);
	}
	return (1);
}

char	**map_generator(char *path)
{
	int		fd;
	char	*map;
	char	*temp;
	char	**map_array;

	if (!ext_validator(path))
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFile not found\n");
		return (NULL);
	}
	temp = NULL;
	map = ft_strdup("");
	while (42)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		map = ft_strjoin(map, temp);
		free(temp);
	}
	close(fd);
	map_array = ft_split(map, '\n');
	free(map);
	return (map_array);
}

void init_img(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map_num_cols, game->map_num_rows, "mlx 42");
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
	int i;
	int j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				put_img(j*TILE_SIZE, i*TILE_SIZE, game, game->wall);
			else if (game->map[i][j] == '0')
				put_img(j*TILE_SIZE, i*TILE_SIZE, game, game->floor);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game game;
	int		count;

	if (argc != 2)
	{
		printf("Usage: ./map_generator <map_file>\n");
		return (0);
	}
	game.map = map_generator(argv[1]);
	if(!game.map)
		return (0);
	if (!wall_validator(&game))
		return (0);
	init_img(&game);
	print_map(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);

	count = 0;
	while (game.map[count])
		free(game.map[count++]);
	free(game.map);
	// mlx_destroy_display(game.mlx);
	// free(game.mlx);

	return (0);
}