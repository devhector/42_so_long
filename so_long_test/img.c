#include <stdio.h>
#include <mlx.h>

int main()
{
		void *mlx;
		void *win;
		void *img;

		char *ima = "../img/img.xpm";

		int		img_width;
		int 	img_height;

		mlx = mlx_init();
		win = mlx_new_window(mlx, 500, 500, "my_mlx");
		img = mlx_xpm_file_to_image(mlx, ima, &img_width, &img_height);
		mlx_put_image_to_window(mlx, win, img, 100, 100);
		mlx_loop(mlx);
		return (0);
}