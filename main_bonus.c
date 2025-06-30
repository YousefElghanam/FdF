/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:30:19 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/30 22:38:01 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	init_map_data(t_map *map)
{
	map->scale = 2;
	map->z_scale = 1;
	map->pos_x = WIDTH / 2;
	map->pos_y = HEIGHT / 2;
	map->angle = 270;
	map->c_angle_x = 30;
	map->c_angle_y = 30;
	map->drag_move = 0;
	map->drag_rotate = 0;
}

static void	init_imgs(t_win *win)
{
	win->img = ft_malloc(sizeof(t_img), 0);
	win->b_img = ft_malloc(sizeof(t_img), 0);
	if (!win->img || !win->b_img)
		return_error(1);
	win->img->ptr = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->b_img->ptr = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!win->img->ptr || !win->b_img->ptr)
		return_error(1);
	win->img->pixels = mlx_get_data_addr(win->img->ptr, &win->img->bpp,
			&win->img->size_len, &win->img->endian);
	win->b_img->pixels = mlx_get_data_addr(win->b_img->ptr, &win->b_img->bpp,
			&win->b_img->size_len, &win->b_img->endian);
	if (!win->img->pixels || !win->b_img->pixels)
		return_error(1);
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

int	all_hooks(t_win *win)
{
	mlx_loop_hook(win->win, draw_to_image, win);
	mlx_key_hook(win->win, move_rotate_keys, win);
	mlx_mouse_hook(win->win, wheel_zoom, win);
	mlx_hook(win->win, 4, (1L << 2), mouse_press, win);
	mlx_hook(win->win, 6, (1L << 6), mouse_drag, win);
	mlx_hook(win->win, 5, (1L << 3), mouse_release, win);
	mlx_hook(win->win, 17, 0, close_window, win);
	return (1);
}

int	main(int argc, char **argv)
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
	all_hooks(&win);
	mlx_loop(win.mlx);
}
