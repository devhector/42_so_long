/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:08:11 by coder             #+#    #+#             */
/*   Updated: 2021/12/10 19:49:59 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>

# define WIDTH 600
# define HEIGHT 400

void draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0

	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
//  pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 10

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0

	double pixelX = beginX;
	double pixelY = beginY;
	
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

typedef struct 
{
	void *mlx;
	void *window;
} t_var;

int	main(void)
{
	void	*ptr;
	void	*win;

	ptr = mlx_init();
	win = mlx_new_window(ptr, WIDTH, HEIGHT, "Criando a janelinha");
	mlx_pixel_put(ptr, win, WIDTH/2, HEIGHT/2, 0x4054B2);
	draw_line(ptr, win, 200, 300, 0, 0, 0xFF2596);
	draw_line(ptr, win, 200, 200, 0, 360, 0xFF2593);
	draw_line(ptr, win, 400, 400, 360, 0, 0xFFFFFF);

	mlx_destroy_window(ptr, win);
	mlx_destroy_display(ptr);
	free(ptr);
	return (0);
}
