#include "fdf.h"

static void	validate_nums(char **arr)
{
	size_t	i;
	
	i = 0;
	while (arr[i] && arr[i][0] != '\n')
	{
		if (!is_valid_int(arr[i]))
			return_error(4);
		i++;
	}
}

static void	validate_line(char *line)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len < 3
		|| line[line_len - 1] != '\n'
		|| line[line_len - 2] != ' ')
		return_error(4);
}

static void	split_validate_line(char *line, size_t *base_width)
{
	char	**string_arr;
	size_t	width;

	validate_line(line);
	string_arr = ft_split(line, ' ');
	width = count_strings(string_arr) - 1; // ( - 1 ) FOR THE '\n'
	add_split_ptrs(string_arr, 1);
	if (*base_width == 0)
		*base_width = width;
	else if (width != *base_width)
		return_error(4);
	validate_nums(string_arr);
}

size_t	validate_map_count_points(int fd)
{
	char	*line;
	size_t	base_width;
	size_t	line_count;

	base_width = 0;
	line_count = 0;
	if (!ft_alloc_list(1))
		return_error(1);
	line = get_next_line(fd);
	check_add_ptr(line, 1, 4);
	while (line)
	{
		line_count++;
		split_validate_line(line, &base_width);
		line = get_next_line(fd);
		ft_add_address(line, 1);
	}
	ft_lstclear(ft_alloc_list(1), &ft_delete);
	return(line_count);
}
