/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:52:42 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/12 21:48:06 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

int	ext_validator(char *path)
{
	int	length;

	length = ft_strlen(path);
	if (ft_strcmp(path + length - 4, ".ber") != 0)
	{
		printf("Error\nInvalid file extension\n");
		return (0);
	}
	return (1);
}

void	find_img_size(t_game *game)
{
	size_t	x;
	int		temp;

	x = 0;
	while (game->map[x])
		x++;
	game->map_num_rows = x * TILE_SIZE;
	game->map_num_cols = (ft_strlen(game->map[0])) * TILE_SIZE;
	x = 0;
	temp = 0;
	while (game->map[x])
	{
		if(game->big_col < temp)
			game->big_col = temp;
		temp = ft_strlen(game->map[x]);
		x++;
	}
}

void	count_map_elements(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == PLAYER_CHAR)
			{
				game->start_position++;
				game->player.x = x;
				game->player.y = y;
			}
			if (game->map[x][y] == EXIT_CHAR)
				game->end_position++;
			if (game->map[x][y] == COIN_CHAR)
				game->collectibles++;
			y++;
		}
		x++;
	}
}

void	map_init(t_game *game)
{
	game->player.direction = 'd';
	game->player.coins = 0;
	game->collectibles = 0;
	game->start_position = 0;
	game->end_position = 0;
	game->finish = 0;
	game->steps = 0;
}
