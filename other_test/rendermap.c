#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#define WALL "./img/wall.xpm"
#define FLOOR "./img/dirt.xpm"

typedef struct s_game
{
	void *mlx;
	void *win;
} t_game;

void put_img(int x, int y, t_game *game)