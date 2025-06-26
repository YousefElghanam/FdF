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
	if (key == 65451)
	{
		win->map->scale += 1;
		win->map->z_scale += 1;
	}
	if (key == 65453)
	{
		win->map->scale -= 1;
		win->map->z_scale -= 1;
	}
	if (key == 65361)
		win->map->step_x -= 50;
	if (key == 65364)
		win->map->step_y += 50;
	if (key == 65363)
		win->map->step_x += 50;
	if (key == 65362)
		win->map->step_y -= 50;
	if (key == 65434)

		win->map->iso_x_x += 1;
	if (key == 65432)
		win->map->iso_x_x -= 1;
	if (key == 65431)
		win->map->iso_x_y += 1;
	if (key == 65437)
		win->map->iso_x_y -= 1;
	if (key == 65429)
		win->map->iso_y_x += 1;
	if (key == 65430)
		win->map->iso_y_x -= 1;
	if (key == 119)
		win->map->iso_y_y += 1;
	if (key == 115)
		win->map->iso_y_y -= 1;
	draw_to_image(win);
	return (0);
}

int	mouse_win(int button, int x, int y)
{
	ft_printf("(%d) key_clicked at %dx%d\n", button, x, y);
	return (0);
}

int	in_limit(t_map *map, int x, int y)
{
	return (x >= 0 && x < map->width && y >= 0 && y < map->height);
}

int	sx(int x1, int x2)
{
	if (x1 < x2)
		return (1);
	return (-1);
}

int	sy(int y1, int y2)
{
	if (y1 < y2)
		return (1);	
	return (-1);
}

void	dir_x(t_line *line)
{
	if (line->e2 > -line->dy)
	{
		line->err -= line->dy;
		line->x1 += line->sx;
	}
}
void	dir_y(t_line *line)
{
	if (line->e2 < line->dx)
	{
		line->err += line->dx;
		line->y1 += line->sy;
	}
}

void	draw_line(t_img *img, t_point *p1, t_point *p2)
{
	t_line	line;

	line.x1 = p1->pixel_x;
	line.y1 = p1->pixel_y;
	line.x2 = p2->pixel_x;
	line.y2 = p2->pixel_y;
	line.dx = abs(line.x2 - p1->pixel_x);
	line.dy = abs(line.y2 - p1->pixel_y);
	line.sx = sx(line.x1, line.x2);
	line.sy = sy(line.y1, line.y2);
	line.err = line.dx - line.dy;
	while (1)
	{
		if (line.x1 >= 0 && line.x1 < WIDTH && line.y1 >= 0 && line.y1 < HEIGHT)
			*(unsigned int *)(img->pixels
					+ line.y1 * img->size_len
					+ line.x1 * (img->bpp / 8)) = p1->color;
		if (line.x1 == line.x2 && line.y1 == line.y2)
			break ;
		line.e2 = 2 * line.err;
		dir_x(&line);
		dir_y(&line);
	}
}

void	draw_lines(t_map *map, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (in_limit(map, x + 1, y))
				draw_line(img, map->points[y][x], map->points[y][x + 1]);
			if (in_limit(map, x, y + 1))
				draw_line(img, map->points[y][x], map->points[y + 1][x]);
			x++;
		}
		y++;
	}
}

void	points_to_pixels(t_map *map)
{
	t_raw	raw;
	int		x;
	int		y;
	float	iso_x;
	float	iso_y;
	
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			raw.x = x * map->scale;
			raw.y = y * map->scale;
			raw.z = map->points[y][x]->z * map->z_scale;
			iso_x = ((raw.x * map->iso_x_x) - (raw.y * map->iso_x_y)) * COS30;
			iso_y = ((raw.x * map->iso_y_x) + (raw.y * map->iso_y_y)) * SIN30 - raw.z;
			(map->points[y][x])->pixel_x = (int)iso_x + 200 + map->step_x;
			(map->points[y][x])->pixel_y = (int)iso_y + 200 + map->step_y;
			x++;
		}
		y++;
	}
}

int	draw_to_image(t_win *win)
{
	t_img	*img;

	img = ft_malloc(sizeof(t_img), 0);
	if (!img)
		return_error(1);
	img->pixels = mlx_get_data_addr(win->img, &img->bpp, &img->size_len, &img->endian);
	ft_memset(img->pixels, 0x0, img->size_len * HEIGHT);
	points_to_pixels(win->map);
	draw_lines(win->map, img);

	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	return (1);
}

// int	change_projection(int key, t_win *win)
// {
// 	if (key == 65434)
// 		win->map->iso_x_x += 1;
// 	if (key == 65432)
// 		win->map->iso_x_x -= 1;
// 	if (key == 65431)
// 		win->map->iso_x_y += 1;
// 	if (key == 65437)
// 		win->map->iso_x_y -= 1;
// 	if (key == 65429)
// 		win->map->iso_y_x += 1;
// 	if (key == 65430)
// 		win->map->iso_y_x -= 1;
// 	if (key == 65465)
// 		win->map->iso_y_y += 1;
// 	if (key == 65466)
// 		win->map->iso_y_y -= 1;
// 	return (1);
// }

int main(int argc, char **argv)
{
	t_win	win;

	if (!ft_alloc_list(0))
		return_error(1);
	win.map = read_map(argc, argv);
	win.mlx = mlx_init();
	ft_add_address(win.mlx, 0);
	win.map->scale = 3;
	win.map->z_scale = 2;
	win.map->step_x = 1;
	win.map->step_y = 1;
	win.map->iso_x_x = 1;
	win.map->iso_x_y = 1;
	win.map->iso_y_x = 1;
	win.map->iso_y_y = 1;
	win.win = mlx_new_window(win.mlx, WIDTH, HEIGHT, "Test: FdF");
	win.img = mlx_new_image(win.mlx, WIDTH, HEIGHT);

	draw_to_image(&win);
	// mlx_loop_hook(win.mlx, draw_to_image, &win);
	mlx_key_hook(win.win, key_win, &win);
	// mlx_key_hook(win.win, change_projection, &win);
	mlx_loop(win.mlx);
}
