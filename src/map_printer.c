/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:49:20 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/10 02:49:40 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

static void	print_map_aux(t_game *game, int x, int y)
{
	if (game->map[x][y] == '1')
		put_img(y * TILE_SIZE, x * TILE_SIZE, game, game->wall);
	else if (game->map[x][y] == '0')
		put_img(y * TILE_SIZE, x * TILE_SIZE, game, game->floor);
	else if (game->map[x][y] == 'P')
	{
		game->player.x = x;
		game->player.y = y;
		put_img(y * TILE_SIZE, x * TILE_SIZE, game, game->person);
	}
	else if (game->map[x][y] == 'E')
		put_img(y * TILE_SIZE, x * TILE_SIZE, game, game->exit);
	else if (game->map[x][y] == 'C')
		put_img(y * TILE_SIZE, x * TILE_SIZE, game, game->coin);
}

int	print_map(t_game	*game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			print_map_aux(game, i, j);
			j++;
		}
		i++;
	}
	return (0);
}
