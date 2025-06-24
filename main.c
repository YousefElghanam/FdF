#include "fdf.h"

int	key_win(int key, t_win *win)
{
	ft_printf("key (%d) was pressed\n", key);
	if (key == 65307)
	{
		mlx_destroy_image(win->mlx, win->img);
		mlx_destroy_window(win->mlx, win->win);
		mlx_destroy_display(win->mlx);
		return_error(0);
	}
	return (0);
}

int	mouse_win(int button, int x, int y)
{
	ft_printf("(%d) key_clicked at %dx%d\n", button, x, y);
	return (0);
}

int	expose_win(void)
{
	ft_printf("hihihihi\n");
	return (0);
}

void	draw_line(t_win *win)
{
	t_point	*point;
	size_t	sep;
	int	y;
	int	x;
	size_t	y_offset;
	size_t	x_offset;
	
	sep = 20;
	y = 0;
	while (y < win->map->height)
	{
		x = 0;
		while (x < win->map->width)
		{
			// ft_printf("x: %d\ny: %d\n\n", x, y);
			point = win->map->points[y][x];
			ft_printf("x:%d\ny:%d\nz:%d\ncolor:%d\n\n", point->x, point->y, point->z, point->color);
			y_offset = win->img->size_len * (y);
			x_offset = win->img->bpp/8 * (x);
			*(unsigned int *)(win->img->pixels + y_offset + x_offset) = point->z;
			x++;
		}
		y++;
	}
}

int	draw_to_image(t_win *win)
{
	t_img	*img;
	int		point1;
	int		point2;
	int		i;

	i = -1;
	img = ft_malloc(sizeof(t_img), 0);
	if (!img)
		return_error(1);
	img->pixels = mlx_get_data_addr(win->img, &img->bpp, &img->size_len, &img->endian);
	ft_memset(img->pixels, 0x808080, img->size_len * HEIGHT);
	point1 = ((HEIGHT / 4) * img->size_len) + (10 * img->bpp/8);
	point2 = ((HEIGHT / 4) * img->size_len) + (1910 * img->bpp/8);
	draw_line(win);
	// while (i < img.size_len * HEIGHT / 2)
	// {
		// *(unsigned int *)(img.pixels + i + point1) = 0x00FFFF00;
	// 	i += 4;
	// }
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_win	win;

	if (!ft_alloc_list(0))
		return_error(1);
	win.map = read_map(argc, argv);
	win.mlx = mlx_init();
	ft_add_address(win.mlx, 0);
	win.win = mlx_new_window(win.mlx, WIDTH, HEIGHT, "Test: FdF");
	win.img = mlx_new_image(win.mlx, WIDTH, HEIGHT);

	mlx_loop_hook(win.mlx, draw_to_image, &win);
	mlx_key_hook(win.win, key_win, &win);
	mlx_loop(win.mlx);
}
