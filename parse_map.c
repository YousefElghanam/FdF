#include "fdf.h"

static t_point	*new_point(size_t x, size_t y, char *num_string)
{
	t_point	*point;

	point = ft_malloc(sizeof(t_point), 0);
	if (!point)
		return_error(1);
	point->x = x;
	point->y = y;
	point->z = ft_atoi(num_string);
	return (point);
}

static void	add_line_points(t_map *map, size_t y, char *line)
{
	char	**string_arr;
	t_point	*point;
	t_point	**point_arr;
	size_t	width;
	size_t	x;

	string_arr = ft_split(line, ' ');
	add_split_ptrs(string_arr, 1);
	width = count_strings(string_arr) - 1;
	map->width = width;
	point_arr = ft_malloc(sizeof(t_point *) * width, 0);
	if (!point_arr)
		return_error(1);
	x = 0;
	while (x < width)
	{
		point = new_point(x, y, string_arr[x]);
		point_arr[x] = point;
		x++;
	}
	(map->points)[y] = point_arr;
}

static void	store_points(t_map *map, int fd, size_t line_count)
{
	char	*line;
	size_t	y;

	y = 0;
	map->height = line_count;
	while (y < line_count)
	{
		line = get_next_line(fd);
		check_add_ptr(line, 1, 1);
		add_line_points(map, y, line);
		y++;
	}
}

int	open_parse_map(t_map *map, char **argv, size_t line_count)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return_error(3);
	map->points = ft_malloc(sizeof(void *) * line_count, 0);
	if (!map->points || !ft_alloc_list(1))
		return_error(1);
	store_points(map, fd, line_count);
	ft_lstclear(ft_alloc_list(1), &ft_delete);
	return (fd);
}
