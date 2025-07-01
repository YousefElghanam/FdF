/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:28:35 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/07/01 12:57:37 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	validate_nums(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (!is_valid_point(arr[i]))
			return_error(4);
		i++;
	}
}

static void	split_validate_line(char *line, size_t *base_width)
{
	char	**string_arr;
	size_t	width;

	string_arr = ft_split(line, ' ');
	width = count_strings(string_arr);
	add_split_ptrs(string_arr, 1);
	if (*base_width == 0)
		*base_width = width;
	else if (width != *base_width)
		return_error(4);
	validate_nums(string_arr);
}

static void	validate_line_len(size_t line_len)
{
	if (line_len < 2 || line_len > 1073741823)
		return_error(4);
}

static void	validate_line_count(size_t line_count)
{
	if (line_count < 1 || line_count > 1073741823)
		return_error(4);
}

size_t	validate_map(int fd)
{
	char	*line;
	size_t	base_width;
	size_t	line_count;
	size_t	line_len;

	base_width = 0;
	line_count = 0;
	if (!ft_alloc_list(1))
		return_error(1);
	line = get_next_line(fd);
	ft_check_add(line, 1, 1);
	while (line)
	{
		line_count++;
		line_len = ft_strlen(line);
		validate_line_len(line_len);
		if (line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		split_validate_line(line, &base_width);
		line = get_next_line(fd);
		ft_add_address(line, 1);
	}
	ft_lstclear(ft_alloc_list(1), &ft_delete);
	validate_line_count(line_count);
	return (line_count);
}
