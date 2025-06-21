#include "fdf.h"

static void	validate_nums(char **arr)
{
	size_t	i;
	
	i = 0;
	while (arr[i++])
	{
		if (!is_valid_int(arr[i - 1]))
		{
			ft_printf("num str is: %s\n", arr[i - 1]);
			return_error(4);
		}
	}
}

void	split_validate_line(char *line, size_t *base_width)
{
	char	**string_arr;
	size_t	width;

	string_arr = ft_split(line, ' ');
	width = count_strings(string_arr);
	add_split_ptrs(string_arr);
	if (width < 1)
		return_error(4);
	if (!*base_width)
		*base_width = width;
	else if (width != *base_width)
		return_error(4);
	validate_nums(string_arr);
}

void	validate_map(int fd)
{
	char	*line;
	size_t	base_width;

	base_width = 0;
	if (!ft_alloc_list(1))
		return_error(1);
	line = get_next_line(fd);
	check_add_ptr(line, 1, 4);
	while (line)
	{
		ft_printf("line is: %s\n", line);
		split_validate_line(line, &base_width);
		line = get_next_line(fd);
	}
	ft_lstclear(ft_alloc_list(1), &ft_delete);
}
