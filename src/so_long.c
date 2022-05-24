/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:56:13 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/09 23:56:08 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: ./so_long <map_file>\n");
		return (0);
	}
	game.map = map_generator(argv[1]);
	if (!game.map)
		return (0);
	if (!map_validator(&game))
	{
		map_free(game.map);
		return (0);
	}
	init_img(&game);
	print_map(&game);
	mlx_hook(game.win, 2, 1L << 0, &key_hook, &game);
	mlx_hook(game.win, 17, 1L << 2, &close_game, &game);
	mlx_hook(game.win, 9, 1L << 21, &print_map, &game);
	mlx_loop_hook(game.mlx, &print_map, &game);
	mlx_loop(game.mlx);
	return (0);
}
