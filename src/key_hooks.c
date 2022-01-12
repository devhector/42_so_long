/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:52:32 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/09 11:53:48 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

void	map_free(char **map)
{
	int	x;

	x = 0;
	while (map[x])
	{
		free(map[x]);
		x++;
	}
	free(map);
}

int	close_game(t_game *game)
{
	int	x;

	x = 0;
	mlx_destroy_image(game->mlx, game->wall);
	mlx_destroy_image(game->mlx, game->floor);
	mlx_destroy_image(game->mlx, game->exit);
	mlx_destroy_image(game->mlx, game->coin);
	mlx_destroy_image(game->mlx, game->person);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	map_free(game->map);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_game	*game)
{
	if (keycode == KEY_ESC)
	{
		close_game(game);
	}
	else
		move(keycode, game);
	return (0);
}
