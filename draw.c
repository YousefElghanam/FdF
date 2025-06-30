/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:28:22 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/30 22:28:22 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_coordinates(t_map *map, t_co *co, int x, int y)
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
	co->iso_x = (co->rot_x - co->rot_y) * cosf(30 * (PI / 180.0f));
	co->iso_y = (co->rot_x + co->rot_y) * sinf(30 * (PI / 180.0f)) - co->raw_z;
}

static void	points_to_pixels(t_map *map)
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

int	draw_to_image(t_win *win)
{
	clear_img(win->img);
	points_to_pixels(win->map);
	if (win->map->scale >= MX_SCAL || win->map->z_scale >= MX_SCAL
		|| win->map->pos_x > 1000 * WIDTH
		|| win->map->pos_y > 1000 * HEIGHT)
		return_error(1);
	draw_map(win->map, win->img);
	mlx_put_image_to_window(win->mlx, win->win, win->img->ptr, 0, 0);
	return (0);
}
