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

int	is_valid_int(char *str)
{
	size_t	i;
	size_t	strlen;

	i = 0;
	if (*str == 0)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	strlen = ft_strlen(str);
	while (i < strlen)
		if (!ft_isdigit(str[i++]))
			return (0);
	if (ft_atoi_but_better(str) == 2147483648)
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