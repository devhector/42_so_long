/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:28:32 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/10 02:45:41 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

static void	print_steps(t_game *game)
{
	game->steps++;
	printf("Steps: %d\n", game->steps);
}

static void	move_player(t_game	*game, int x, int y)
{
	int	px;
	int	py;

	px = game->player.x;
	py = game->player.y;
	if (game->map[x][y] != '1' && game->map[x][y] != EXIT_CHAR)
	{
		if (game->map[x][y] == COIN_CHAR)
		{
			game->player.coins++;
			game->collectibles--;
		}
		game->player.x = x;
		game->player.y = y;
		game->map[px][py] = '0';
		game->map[x][y] = PLAYER_CHAR;
		print_steps(game);
	}
	else if (game->map[x][y] == EXIT_CHAR && !game->collectibles)
	{
		game->finish = 1;
		game->map[px][py] = '0';
		print_steps(game);
	}
	print_map(game);
}

void	move(int keycode, t_game	*game)
{
	int	px;
	int	py;

	px = game->player.x;
	py = game->player.y;
	if (game->finish != 0)
		return ;
	if (keycode == KEY_A)
	{
		game->player.direction = 'a';
		mlx_destroy_image(game->mlx, game->person);
		game->person = load_img(game, PERSON_A);
		move_player(game, px, py - 1);
	}
	else if (keycode == KEY_D)
	{
		game->player.direction = 'd';
		mlx_destroy_image(game->mlx, game->person);
		game->person = load_img(game, PERSON_D);
		move_player(game, px, py + 1);
	}
	else if (keycode == KEY_W)
		move_player(game, px - 1, py);
	else if (keycode == KEY_S)
		move_player(game, px + 1, py);
}
