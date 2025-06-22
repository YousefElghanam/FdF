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

t_map	*read_map(int argc, char **argv)
{
	// t_map	map;
	int		fd;

	fd = open_validate_file(argc, argv);
	validate_map(fd);
	return(NULL);
}
