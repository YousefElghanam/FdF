#include "fdf.h"

void	init_map_data(t_map *map)
{
	map->scale = 2;
	map->z_scale = 2;
	map->pos_x = WIDTH / 2;
	map->pos_y = HEIGHT / 2;
	map->angle = 270;
	map->drag_move = 0;
	map->drag_rotate = 0;
}

int	handle_mouse_zoom(int key, int x, int y, t_win *win)
{
	ft_printf("mouse(%d) at (%d,%d)\n", key, y, x);
	if (key == 4)
	{
		win->map->scale += 0.2;
		win->map->z_scale += 0.2;
	}
	else if (key == 5)
	{
		win->map->scale -= 0.2;
		win->map->z_scale -= 0.2;
	}
	draw_to_image(win);
	return (0);
}

int	close_window(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img->ptr);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	return_error(0);
	return (0);
}

int	handle_keys(int key, t_win *win)
{
	if (key == 65307)
		close_window(win);
	return (0);
}

int	in_limit(t_map *map, int x, int y)
{
	return (x >= 0 && x < map->width && y >= 0 && y < map->height);
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

void	set_line_data(t_line *line, t_point *p1, t_point *p2)
{
	line->x1 = p1->pixel_x;
	line->y1 = p1->pixel_y;
	line->x2 = p2->pixel_x;
	line->y2 = p2->pixel_y;
	line->dx = abs(line->x2 - line->x1);
	line->dy = abs(line->y2 - line->y1);
	if (line->x1 < line->x2)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y1 < line->y2)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

void	draw_line(t_img *img, t_point *p1, t_point *p2)
{
	t_line	line;

	set_line_data(&line, p1, p2);
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

void	draw_map(t_map *map, t_img *img)
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

void	set_coordinates(t_map *map, t_co *co, int x, int y)
{
	co->raw_x = x * map->scale;
	co->raw_y = y * map->scale;
	co->raw_z = map->points[y][x]->z * map->z_scale;
	co->cx = (map->width * map->scale) * 0.5f;
	co->cy = (map->height * map->scale) * 0.5f;
	co->cos = cosf(map->angle * (PI / 180.0f));
	co->sin = sinf(map->angle * (PI / 180.0f));
	co->rot_x = (co->raw_x - co->cx) * co->cos - (co->raw_y - co->cy) * co->sin;
	co->rot_y = (co->raw_x - co->cx) * co->sin + (co->raw_y - co->cy) * co->cos;
	co->raw_x = co->rot_x;
	co->raw_y = co->rot_y;
	co->iso_x = (co->raw_x - co->raw_y) * cosf(30 * (PI / 180.0f));
	co->iso_y = (co->raw_x + co->raw_y) * sinf(30 * (PI / 180.0f)) - co->raw_z;
}

void	points_to_pixels(t_map *map)
{
	t_co	co;
	int		x;
	int		y;
	
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			set_coordinates(map, &co, x, y);
			(map->points[y][x])->pixel_x = (int)co.iso_x + map->pos_x;
			(map->points[y][x])->pixel_y = (int)co.iso_y + map->pos_y;
			x++;
		}
		y++;
	}
}

void	swap_imgs(t_win *win)
{
	t_img	*tmp;

	tmp = win->img;
	win->img = win->b_img;
	win->b_img = tmp;
}

void	init_imgs(t_win *win)
{
	win->img = ft_malloc(sizeof(t_img), 0);
	if (!win->img)
		return_error(1);
	win->img->ptr = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!win->img->ptr)
		return_error(1);
	win->img->pixels = mlx_get_data_addr(win->img->ptr, &win->img->bpp, &win->img->size_len, &win->img->endian);
	if (!win->img->pixels)
		return_error(1);
}

void	clear_img(t_img *img)
{
	uint32_t	*p;
	size_t		pixels;

	p = (uint32_t *)img->pixels;
	pixels = img->size_len * HEIGHT / sizeof(*p);
	while (pixels--)
		*p++ = 0x00000000;
}

int	draw_to_image(t_win *win)
{
	clear_img(win->img);
	points_to_pixels(win->map);
	draw_map(win->map, win->img);
	mlx_put_image_to_window(win->mlx, win->win, win->img->ptr, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_win	win;

	if (!ft_alloc_list(0))
		return_error(1);
	win.map = read_map(argc, argv);
	win.mlx = ft_check_add(mlx_init(), 0, 1);
	win.win = ft_check(mlx_new_window(win.mlx, WIDTH, HEIGHT, "FdF"), 1);
	init_map_data(win.map);
	init_imgs(&win);
	draw_to_image(&win);
	mlx_key_hook(win.win, handle_keys, &win);
	mlx_mouse_hook(win.win, handle_mouse_zoom, &win);
	mlx_hook(win.win, 17, 0, close_window, &win);
	mlx_loop(win.mlx);
}
