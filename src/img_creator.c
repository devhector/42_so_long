/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:41:24 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/07 17:45:33 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

void	*load_img(t_game	*game, char	*path)
{
	int		x;
	int		y;
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, path, &x, &y);
	if (img == NULL)
	{
		printf("Error\nImage not found\n");
		exit(1);
	}
	return (img);
}

void	init_img(t_game	*game)
{
	game->player.direction = 'd';
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map_num_cols, \
	game->map_num_rows, "so_long");
	game->wall = load_img(game, WALL);
	game->floor = load_img(game, FLOOR);
	game->person = load_img(game, PERSON_D);
	game->exit = load_img(game, EXIT);
	game->coin = load_img(game, COIN);
}

void	put_img(int x, int y, t_game	*game, void	*img)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x, y);
}
