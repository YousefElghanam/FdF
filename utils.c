#include "fdf.h"

void	*check_add_ptr(void *ptr, int list_num, int error_num)
{
	if (!ptr)
		return_error(error_num);
	ft_add_address(ptr, list_num);
	return (ptr);
}

size_t	count_strings(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

size_t	ft_strlen_till_comma(char *str)
{
	if (ft_strchr(str, ',') == NULL)
		return(ft_strlen(str));
	else if ((size_t)(ft_strchr(str, ',') - str) == 0)
		return_error(4);
	return ((size_t)(ft_strchr(str, ',') - str));
}

int	is_valid_hex(char *str)
{
	size_t	i;
	char	c;

	i = 2;
	if (ft_strlen(str) < 3 || ft_strlen(str) > 10)
		return (0);
	if (str[0] != '0' || str[1] != 'x')
		return (0);
	while (str[i])
	{
		c = str[i];
		if (!ft_isdigit(c)
			|| !(('A' <= c && c <= 'F') || ('a' <= c && c <= 'f')))
			return (0);
		i++;
	}
	return (1);
}

void	validate_color_hex(char *str, size_t strlen)
{
	char	*color;

	color = ft_substr(str, strlen + 1, ft_strlen(str) - strlen);
	check_add_ptr(color, 1, 1);
	if (ft_strchr(color, ',') && !is_valid_hex(color))
		return_error(4);
}

int	is_valid_int(char *str)
{
	size_t	i;
	size_t	strlen;
	char	*num;

	i = 0;
	if (*str == 0)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	strlen = ft_strlen_till_comma(str);
	while (i < strlen)
		if (!ft_isdigit(str[i++]))
			return (0);
	if (ft_strchr(str, ','))
		validate_color_hex(str, strlen);
	num = ft_substr(str, 0, strlen);
	check_add_ptr(num, 1, 1);
	if (ft_atoi_but_better(num) == 2147483648)
		return (0);
	return (1);
}

void	add_split_ptrs(char **arr, int list_num)
{
	size_t	i;

	i = 0;
	check_add_ptr(arr, list_num, 1);
	while (arr[i])
	{
		ft_add_address(arr[i], list_num);
		i++;
	}
}