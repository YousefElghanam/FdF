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

int	draw_to_image(t_win *win)
{
	t_img	img;
	int		offset;
	int		i;

	i = -1;
	img.pixels = mlx_get_data_addr(win->img, &img.bpp, &img.size_len, &img.endian);
	ft_memset(img.pixels, 0xFF, img.size_len * HEIGHT);
	offset = (450 * img.size_len) + (0 * img.bpp/8);
	while (i++ < img.size_len)
	{
		img.pixels[offset + 0] = (char)0x55; //mlx_get_color_value(win->mlx, 0x1155); //(char)0x00;
		img.pixels[offset + 1] = (char)0x55; //mlx_get_color_value(win->mlx, 0x2255);
		img.pixels[offset + 2] = (char)0x55; //mlx_get_color_value(win->mlx, 0x2255);
		img.pixels[offset + 3] = (char)0x55; //mlx_get_color_value(win->mlx, 0x00);
	}
	//mlx_get_color_value(win->mlx, 0x00FF0000);
	// *((unsigned int *)(pixels + offset)) = 0x00FFFFFF;
	// pixels[offset + 4] = mlx_get_color_value(win->mlx, 0x0000FF);
	// pixels[offset + 8] = mlx_get_color_value(win->mlx, 0x0000FF);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	return (1);
}

int	main(void)
{
	t_win	win;

	if (!ft_alloc_list())
		return_error(1);
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 1600, 900, "Test: FdF");
	win.img = mlx_new_image(win.mlx, 1600, 900);

	mlx_loop_hook(win.mlx, draw_to_image, &win);
	mlx_key_hook(win.win, key_win, &win);
	mlx_loop(win.mlx);
}
