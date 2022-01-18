#include "minilibx_macos/mlx.h"

int WIDTH = 1300;
int	HEIGHT = 1200;

typedef struct s_data {
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_lentgh;
	int		endian;
}	t_data;

typedef struct s_drawer{
	void *mlx;
	void *window;
	t_data	data;
}	t_drawer;

void	optimized_pixelput(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data -> address + (y * data->line_lentgh + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void print_square(t_drawer drawer, int x, int y, int z)
{
	for(int i = 0; i <= 1000; i++)
	{
		for (int j = 0; j <= 1000; j++)
		{
			if (((j == 10 || j == 1000) && i >= 10 )|| ((i == 10 || i == 1000) && j >= 10) )
				optimized_pixelput(&drawer.data, x + i/z, y + j/z, 0x01FF0000);
		}
	}
	mlx_put_image_to_window(drawer.mlx, drawer.window, drawer.data.image, x, y);
}

void print_circle(void *mlx, void *window, t_data img, int x, int y)
{
	for(int i = 0; i < 500; i++)
		for (int j = 0; j < 500; j++)
			optimized_pixelput(&img, i + j , i + j, 0x0100FF00);
	mlx_put_image_to_window(mlx, window, img.image, x, y);
}

int	main(void)
{
	void	*mlx = mlx_init();
	void	*window = mlx_new_window(mlx, WIDTH, HEIGHT, "Chocapic");
	t_drawer	drawer;
	t_data	img;
	
	img.image = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.line_lentgh, &img.endian);
	drawer.data = img;
	drawer.window = window;
	drawer.mlx = mlx;
	print_square(drawer, 50, 50, 3);
	//print_square(drawer, 100, 100, 2);
	print_circle(mlx, window, img, 10, 10);
	mlx_loop(mlx);
	/*mlx_pixel_put(mlx, window, 10, 10, 0x00FF0000);
	mlx_pixel_put(mlx, window, 20, 10, 0x00FF0000);
	mlx_pixel_put(mlx, window, 30, 10, 0x00FF0000);
	mlx_string_put(mlx, window, 50, 50, 0x00FFFFFF, "Chocapic");*/
}