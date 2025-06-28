#include "fdf.h"

void	init_map_data(t_map *map)
{
	map->scale = 4;
	map->z_scale = 1;
	map->pos_x = WIDTH / 2;
	map->pos_y = HEIGHT / 2;
	map->angle = 270;
	map->drag_move = 0;
	map->drag_rotate = 0;
}

int	wheel_zoom(int key, int x, int y, t_win *win)
{
	ft_printf("mouse clicked at (%d, %d)\n", y, x);
	if (key == 4)
	{
		win->map->scale += 1;
		win->map->z_scale += 1;
	}
	else if (key == 5)
	{
		win->map->scale -= 1;
		win->map->z_scale -= 1;
	}
	draw_to_image(win);
	return (1);
}

int	mouse_press(int key, int x, int y, t_win *win)
{
	ft_printf("mouse(%d) press(%d, %d)\n", key, y, x);
	if (key == 1)
	{
		win->map->drag_move = 1;
		win->map->mouse_pos_x = x;
		win->map->mouse_pos_y = y;
		win->map->org_pos_x = win->map->pos_x;
		win->map->org_pos_y = win->map->pos_y;
	}
	else if (key == 3)
	{
		win->map->drag_move = 0;
		win->map->drag_rotate = 1;
		win->map->mouse_pos_x = x;
		win->map->org_angle = win->map->angle;
	}
	wheel_zoom(key, x, y, win);
	return (1);
}

int	mouse_drag(int x, int y, t_win *win)
{
	if (win->map->drag_move)
	{
		win->map->pos_x = win->map->org_pos_x + (x - win->map->mouse_pos_x);
		win->map->pos_y = win->map->org_pos_y + (y - win->map->mouse_pos_y);
		draw_to_image(win);
	}
	else if (win->map->drag_rotate)
	{
		win->map->angle = win->map->org_angle + (win->map->mouse_pos_x - x) / 15;
		draw_to_image(win);
	}
	return (1);
}

int	mouse_release(int key, int x, int y, t_win *win)
{
	ft_printf("mouse(%d) released at (%d, %d)\n", key, y, x);
	if (key == 1)
		win->map->drag_move = 0;
	if (key == 3)
		win->map->drag_rotate = 0;
	return (1);
}

int	close_window(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img->ptr);
	mlx_destroy_image(win->mlx, win->b_img->ptr);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	return_error(0);
	return (1);
}

int	move_rotate_keys(int key, t_win *win)
{
	ft_printf("key (%d) pressed\n", key);
	if (key == 65307)
		close_window(win);
	else if (key == 65361)
		win->map->pos_x += 50;
	else if (key == 65362)
		win->map->pos_y += 50;
	else if (key == 65364)
		win->map->pos_y -= 50;
	else if (key == 65363)
		win->map->pos_x -= 50;
	else if (key == 65432)
		win->map->angle += 15.0f;
	else if (key == 65430)
		win->map->angle -= 15.0f;
	draw_to_image(win);
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
	line->dx = abs(line->x2 - p1->pixel_x);
	line->dy = abs(line->y2 - p1->pixel_y);
	line->sx = (line->x1 < line->x2) - (line->x1 > line->x2);
	line->sy = (line->y1 < line->y2) - (line->y1 > line->y2);
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

// void	draw_circle_point(t_img *img, t_point *p)
// {
// 	*(unsigned int *)(img->pixels + p->pixel_y * img->size_len + p->pixel_x * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y + 0) * img->size_len + (p->pixel_x + 1) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y + 1) * img->size_len + (p->pixel_x + 1) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y - 1) * img->size_len + (p->pixel_x + 1) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y + 0) * img->size_len + (p->pixel_x - 1) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y + 1) * img->size_len + (p->pixel_x - 1) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y - 1) * img->size_len + (p->pixel_x - 1) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y + 1) * img->size_len + (p->pixel_x + 0) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y - 1) * img->size_len + (p->pixel_x + 0) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y + 0) * img->size_len + (p->pixel_x + 2) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y + 0) * img->size_len + (p->pixel_x - 2) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y + 2) * img->size_len + (p->pixel_x + 0) * img->bpp / 8) = 0xFF0000;
// 	*(unsigned int *)(img->pixels + (p->pixel_y - 2) * img->size_len + (p->pixel_x + 0) * img->bpp / 8) = 0xFF0000;
// }

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
			// draw_circle_point(img, map->points[y][x]);
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
	win->b_img = ft_malloc(sizeof(t_img), 0);
	if (!win->img || !win->b_img)
		return_error(1);
	win->img->ptr = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->b_img->ptr = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!win->img->ptr || !win->b_img->ptr)
		return_error(1);
	win->img->pixels = mlx_get_data_addr(win->img->ptr, &win->img->bpp, &win->img->size_len, &win->img->endian);
	win->b_img->pixels = mlx_get_data_addr(win->b_img->ptr, &win->b_img->bpp, &win->b_img->size_len, &win->b_img->endian);
	if (!win->img->pixels || !win->b_img->pixels)
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
	ft_printf("img:%p == b_img:%p\n", win->img, win->b_img);
	clear_img(win->b_img);
	points_to_pixels(win->map);
	draw_map(win->map, win->b_img);
	mlx_put_image_to_window(win->mlx, win->win, win->b_img->ptr, 0, 0);
	swap_imgs(win);
	return (1);
}

int main(int argc, char **argv)
{
	t_win	win;

	if (!ft_alloc_list(0))
		return_error(1);
	win.map = read_map(argc, argv);
	win.mlx = mlx_init();
	if (!win.mlx)
		return_error(1);
	ft_add_address(win.mlx, 0);
	init_map_data(win.map);
	win.win = mlx_new_window(win.mlx, WIDTH, HEIGHT, "FdF");
	if (!win.win)
		return_error(1);
	init_imgs(&win);
	// draw_to_image(&win);
	mlx_key_hook(win.win, move_rotate_keys, &win);
	mlx_mouse_hook(win.win, wheel_zoom, &win);
	mlx_loop_hook(win.mlx, draw_to_image, &win);
	mlx_hook(win.win, 4, (1L<<2), mouse_press, &win);
	mlx_hook(win.win, 6, (1L<<6), mouse_drag, &win);
	mlx_hook(win.win, 5, (1L<<3), mouse_release, &win);
	mlx_hook(win.win, 17, 0, close_window, &win);
	mlx_loop(win.mlx);
}
