/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:31:30 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/13 15:21:52 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

static int	is_rectangle(t_game *game)
{
	int	colums;
	int	temp;
	int	x;

	x = 0;
	colums = game->map_num_cols / TILE_SIZE;
	while (x < (game->map_num_rows / TILE_SIZE))
	{
		temp = ft_strlen(game->map[x]);
		if (temp != colums)
		{
			printf("Error\nMap should be rectangle\n");
			return (0);
		}
		x++;
	}
	return (1);
}

int	wall_validator(t_game *game)
{
	int	x;
	int	y;
	int	rows;
	int	colums;

	x = 0;
	y = 0;
	rows = (game->map_num_rows / TILE_SIZE) - 1;
	colums = (game->map_num_cols / TILE_SIZE) - 1;
	while (game->map[0][y] == '1' && game->map[rows][y] == '1' && y <= colums)
		y++;
	while (game->map[x][0] == '1' && game->map[x][colums] == '1' && x < rows)
		x++;
	if (--y != colums || x != rows)
	{
		printf("Error\nMap must be surrounded by walls\n");
		return (0);
	}
	return (1);
}

int	map_validator(t_game *game)
{
	int	start_position;
	int	end_position;
	int	collectibles;

	map_init(game);
	count_map_elements(game);
	find_img_size(game);
	start_position = game->start_position;
	end_position = game->end_position;
	collectibles = game->collectibles;
	if (!is_rectangle(game))
		return (0);
	if (!wall_validator(game))
		return (0);
	if (start_position != 1 || end_position != 1 || collectibles < 1)
	{
		printf("Error\nMap must have exactly one player, ");
		printf("one exit and at least one collectible.\n");
		return (0);
	}
	return (1);
}
