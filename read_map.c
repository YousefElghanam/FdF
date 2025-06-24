#include "fdf.h"

// TODO: GIVE "HOW TO USE PROGRAM" ERROR ON UNEXPECTED INPUT
static int	open_validate_file(int argc, char **argv)
{
	size_t	file_len;
	char	*file;
	int		fd;

	if (argc < 2)
		return_error(5);
	file = argv[1];
	file_len = ft_strlen(file);
	if (file_len < 5)
		return_error(3);
	if (ft_strncmp(&file[file_len - 4], ".fdf", 4) != 0)
		return_error(3);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return_error(3);
	return(fd);
}

void	test_map_parsing(t_map *map)
{
	int	i;
	int	x;

	i = 0;
	while(i < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("point(%d:%d):\ny:%d\nx:%d\nz:%d\ncolor:%d", i, x, (map->points[i])[x]->y, (map->points[i])[x]->x, (map->points[i])[x]->z, (map->points[i])[x]->color);
			ft_printf("\n");
			x++;
		}
		i++;
	}
}

t_map	*read_map(int argc, char **argv)
{
	t_map	*map;
	size_t	line_count;
	int		fd;

	fd = open_validate_file(argc, argv);
	line_count = validate_map(fd);
	map = ft_malloc(sizeof(t_map), 0);
	if (!map)
		return_error(1);
	close(fd);
	// ft_printf("line count is: %d\n", line_count);
	fd = open_parse_map(map, argv, line_count);
	close(fd);
	// test_map_parsing(&map);
	return(map);
}
