/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:27:18 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/30 22:32:05 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_line_data(t_line *line, t_point *p1, t_point *p2)
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
	if (line->dx > line->dy)
		line->max_steps = line->dx;
	else
		line->max_steps = line->dy;
	line->step = 0;
	line->err = line->dx - line->dy;
}

static void	draw_line(t_img *img, t_point *p1, t_point *p2)
{
	t_line	line;

	set_line_data(&line, p1, p2);
	while (1)
	{
		if (line.x1 >= 0 && line.x1 < WIDTH && line.y1 >= 0 && line.y1 < HEIGHT)
		{
			if (line.max_steps)
				line.t = (float)line.step / line.max_steps;
			else
				line.t = 0.0f;
			*(unsigned int *)(img->pixels
					+ line.y1 * img->size_len
					+ line.x1 * (img->bpp / 8))
				= calc_color(p1->color, p2->color, line.t);
		}
		if (line.x1 == line.x2 && line.y1 == line.y2)
			break ;
		line.e2 = 2 * line.err;
		dir_x(&line);
		dir_y(&line);
		line.step++;
	}
}

void	draw_map(t_map *map, t_img *img)
{
	int	x;
	int	y;

	if (map->scale > MX_SCAL)
		return_error(1);
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
