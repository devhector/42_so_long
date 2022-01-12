/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:55:18 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/12 21:51:53 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define WALL "./img/wall.xpm"
# define FLOOR "./img/dirt.xpm"
# define COIN "./img/coin.xpm"
# define EXIT "./img/exit.xpm"
# define PERSON_D "./img/person_d.xpm"
# define PERSON_A "./img/person_a.xpm"

# define COIN_CHAR 'C'
# define EXIT_CHAR 'E'
# define PLAYER_CHAR 'P'

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

# define TILE_SIZE 32

# include "../lib/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
	int		coins;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*wall;
	void		*floor;
	void		*person;
	void		*coin;
	void		*exit;
	char		**map;
	int			map_num_rows;
	int			map_num_cols;
	int			collectibles;
	int			start_position;
	int			end_position;
	int			finish;
	int			steps;
	int			big_col;
	t_player	player;
}	t_game;

int		close_game(t_game *game);
int		ext_validator(char *path);
int		print_map(t_game	*game);
int		map_validator(t_game *game);
int		wall_validator(t_game *game);
int		key_hook(int keycode, t_game *game);

char	**map_generator(char *path);

void	map_free(char **map);
void	init_img(t_game	*game);
void	map_init(t_game *game);
void	find_img_size(t_game *game);
void	count_map_elements(t_game *game);
void	move(int keycode, t_game	*game);
void	*load_img(t_game	*game, char	*path);
void	put_img(int x, int y, t_game	*game, void	*img);

#endif