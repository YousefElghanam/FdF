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

// int	my_draw_to_window(t_win *win)
// {
// 	int i = 20;
	
// 	// mlx_expose_hook(win->win, my_draw_to_window, NULL);
// 	return (1);
// }

void	draw_to_image(t_win *win)
{
	char	*pixels;
	int		bpp;
	int		size_len;
	int		endian;
	int		offset;
	
	bpp = 32; 
	size_len = 4 * 800;
	endian = 0;
	win->img = mlx_new_image(win->mlx, 800, 600);
	pixels = mlx_get_data_addr(win->img, &bpp, &size_len, &endian);
	offset = (20 * bpp/8) + (10 * size_len);
	pixels[offset + 1] = mlx_get_color_value(win->mlx, 0x00FF00);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
}

int	main(void)
{
	void	*mlx_ptr;
	t_win	*win1;

	if (!ft_alloc_list())
		return_error(1);
	ft_add_address(mlx_ptr = mlx_init());
	if (!mlx_ptr)
		return_error(1);
	win1 = ft_malloc(sizeof(t_win));
	win1->mlx = mlx_ptr;
	win1->win = mlx_new_window(mlx_ptr, 800, 600, "Hi, FdF");
	mlx_key_hook(win1->win, key_win, win1);

	draw_to_image(win1);

	mlx_loop(mlx_ptr);
}
