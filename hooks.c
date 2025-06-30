/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:27:27 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/30 22:27:27 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mouse_zoom(int key, int x, int y, t_win *win)
{
	(void)x;
	(void)y;
	if (key == 4 && win->map->scale < MX_SCAL && win->map->z_scale < MX_SCAL)
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

int	handle_keys(int key, t_win *win)
{
	if (key == 65307)
		close_window(win);
	return (0);
}
