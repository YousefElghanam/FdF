#include "fdf.h"

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
	size_t	i;

	i = 0;
	if (str[i] == ',')
		return_error(4);
	while (str[i] && str[i] != ',')
		i++;
	return (i);
}

int	is_valid_hex(char *str)
{
	size_t	i;
	char	c;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (str[i++] != '0' || (str[i] != 'X' && str[i] != 'x'))
		return (0);
	if (str[++i] == 0)
		return (0);
	while (str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 6 || ft_strlen(str) > 30)
		return (0);
	while (str[i])
	{
		c = str[i];
		if (!ft_isdigit(c)
			&& !(('A' <= c && c <= 'F') || ('a' <= c && c <= 'f')))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_point(char *str)
{
	size_t	i;
	size_t	strlen;

	i = 0;
	if (*str == 0)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	strlen = ft_strlen_till_comma(str);
	while (i < strlen)
		if (!ft_isdigit(str[i++]))
			return (0);
	if (str[i] == ',' && !is_valid_hex(str + strlen + 1))
		return_error(4);
	if (ft_atoi_but_better(str) == 2147483648)
		return (0);
	return (1);
}

void	add_split_ptrs(char **arr, int list_num)
{
	size_t	i;

	i = 0;
	ft_check_add(arr, list_num, 1);
	while (arr[i])
	{
		ft_add_address(arr[i], list_num);
		i++;
	}
}
