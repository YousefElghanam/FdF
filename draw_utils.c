/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:27:47 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/30 22:27:48 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

unsigned int	calc_color(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = ((1 - t) * ((c1 >> 16) & 0xFF)) + (t * ((c2 >> 16) & 0xFF));
	g = ((1 - t) * ((c1 >> 8) & 0xFF)) + (t * ((c2 >> 8) & 0xFF));
	b = ((1 - t) * ((c1) & 0xFF)) + (t * ((c2) & 0xFF));
	return ((r << 16) | (g << 8) | b);
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
