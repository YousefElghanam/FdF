/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:30:36 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/30 22:31:33 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_map_data(t_map *map)
{
	map->scale = 4;
	map->z_scale = 4;
	map->pos_x = WIDTH / 2;
	map->pos_y = HEIGHT / 2;
	map->angle = 270;
}

static void	init_imgs(t_win *win)
{
	win->img = ft_malloc(sizeof(t_img), 0);
	if (!win->img)
		return_error(1);
	win->img->ptr = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!win->img->ptr)
		return_error(1);
	win->img->pixels = mlx_get_data_addr(win->img->ptr, &win->img->bpp,
			&win->img->size_len, &win->img->endian);
	if (!win->img->pixels)
		return_error(1);
}

int	close_window(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img->ptr);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	return_error(0);
	return (0);
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
	mlx_key_hook(win.win, handle_keys, &win);
	mlx_mouse_hook(win.win, handle_mouse_zoom, &win);
	mlx_hook(win.win, 17, 0, close_window, &win);
	mlx_loop(win.mlx);
}
