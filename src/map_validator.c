/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:31:30 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/12 20:07:35 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

int	is_rectangle(t_game *game)
{
	int	rows;
	int	cols;
	int	x;
	int	y;

	y = 0;
	rows = game->map_num_rows / TILE_SIZE;
	cols = game->map_num_cols / TILE_SIZE;
	while (game->map[x][y++] != '\0')
	{
		x = 0;
		while (game->map[x++][y] != '\0')
		{
			if(x != rows)
			{
				printf("Error\nInvalid map\n");
				return (0);
			}
			printf("%d\n", x);
		}
	}
	x = 0;
	while (game->map[x++][0] != '\0')
	{
		if (ft_strlen(game->map[x]) != cols)
		{
			printf("Error\nInvalid map\n");
			return (0);
		}
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
	find_img_size(game);
	is_rectangle(game);
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
	start_position = game->start_position;
	end_position = game->end_position;
	collectibles = game->collectibles;
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
