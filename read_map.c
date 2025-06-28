#include "fdf.h"

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
	fd = open_parse_map(map, argv, line_count);
	close(fd);
	return(map);
}
