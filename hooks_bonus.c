/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:23:08 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/30 22:41:28 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	wheel_zoom(int key, int x, int y, t_win *win)
{
	(void)x;
	(void)y;
	if (key == 4 && win->map->scale < MX_SCAL && win->map->z_scale < MX_SCAL)
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
		win->map->angle = win->map->org_angle
			+ (win->map->mouse_pos_x - x) / 15;
		draw_to_image(win);
	}
	return (1);
}

int	mouse_release(int key, int x, int y, t_win *win)
{
	(void)x;
	(void)y;
	if (key == 1)
		win->map->drag_move = 0;
	if (key == 3)
		win->map->drag_rotate = 0;
	return (1);
}

int	move_rotate_keys(int key, t_win *win)
{
	ft_printf("key (%d) pressed\n", key);
	if (key == 65307)
		close_window(win);
	else if (key == 65361)
		win->map->pos_x -= 50;
	else if (key == 65362)
		win->map->pos_y -= 50;
	else if (key == 65364)
		win->map->pos_y += 50;
	else if (key == 65363)
		win->map->pos_x += 50;
	else if (key == 119)
		win->map->c_angle_x += 15.0f;
	else if (key == 115)
		win->map->c_angle_x -= 15.0f;
	else if (key == 97)
		win->map->c_angle_y += 15.0f;
	else if (key == 100)
		win->map->c_angle_y -= 15.0f;
	else if (key == 65432)
		win->map->angle += 15.0f;
	else if (key == 65430)
		win->map->angle -= 15.0f;
	draw_to_image(win);
	return (0);
}
