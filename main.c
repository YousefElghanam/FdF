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

#define SCALE 10

// void	put_pixel(t_img *img, t_pixel *p, int color);

void	draw_line(t_img *img, t_pixel *p1, t_pixel *p2);

void	put_map_points(t_map *map, t_img *img)
{
	t_point	*point;
	t_pixel	*pixel;
	int		y;
	int		x;
	int		sep;
	
	y = 0;
	sep = 30;
	pixel = ft_malloc(sizeof(t_pixel), 0);
	if (!pixel)
		return_error(1);
	while (y < map->height)
	{		//bytes per line V 					V y starting map pixel
		pixel->y = img->size_len * ((y * sep) + 200);
		x = 0;
		while (x < map->width)
		{
			// ft_printf("x: %d\ny: %d\n\n", x, y);
			point = map->points[y][x];
			// ft_printf("x:%d\ny:%d\nz:%d\ncolor:%d\n", point->x, point->y, point->z, point->color);
			pixel->x = img->bpp/8 * ((x * sep) + 200);
			pixel->color = point->color;
			draw_line()
			// ft_printf("at pixel (%d,%d)\n\n", pixel->y / img->size_len, pixel->x / 4);
			// check_inbound(); // This needs to be before changing the pixel (next)
			*(unsigned int *)(img->pixels + pixel->y + pixel->x) = point->color;
			x++;
		}
		y++;
	}
}

// void	put_map_points(t_win *win, t_img *img)
// {
// 	t_point	*point;
// 	int		y;
// 	int		x;
// 	int		y_offset;
// 	int		x_offset;
	
// 	y = 0;
// 	while (y < win->map->height)
// 	{
// 		y_offset = img->size_len * y;
// 		x = 0;
// 		while (x < win->map->width)
// 		{
// 			// ft_printf("x: %d\ny: %d\n\n", x, y);
// 			point = win->map->points[y][x];
// 			ft_printf("x:%d\ny:%d\nz:%d\ncolor:%d\n", point->x, point->y, point->z, point->color);
// 			x_offset = img->bpp/8 * (x);
// 			ft_printf("at pixel (%d,%d)\n\n", y, x);
// 			*(unsigned int *)(win->img->pixels + y_offset + x_offset) = point->z;
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
	ft_memset(img->pixels, 0x0, img->size_len * HEIGHT);
	point1 = ((HEIGHT / 4) * img->size_len) + (10 * img->bpp/8);
	point2 = ((HEIGHT / 4) * img->size_len) + (1910 * img->bpp/8);
	put_map_points(win->map, img);
	// while (i < img.size_len * HEIGHT / 2)
	// {
		// *(unsigned int *)(img.pixels + i + point1) = 0x00FFFF00;
	// 	i += 4;
	// }
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	return (1);
}

int main(int argc, char **argv)
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
