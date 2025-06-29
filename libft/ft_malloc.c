/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josefelghnam <josefelghnam@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:06:43 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/29 21:52:16 by josefelghna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// TODO: RECHECK WHETER TO OUTPUT TO STDERR OR STDOUT
void	return_error(int state, ...)
{
	if (state == 1)
		write(2, "Error\n", 6);
	else if (state == 3)
		write(1, "Invalid Map File.\n", 17);
	else if (state == 4)
		write(1, "Invalid Map.\n", 13);
	else if (state == 5)
		write(2, "No arguments given. Usage: (./fdf \"map.fdf\")\n", 45);
	ft_lstclear(ft_alloc_list(0), &ft_delete);
	ft_lstclear(ft_alloc_list(1), &ft_delete);
	free(ft_alloc_list(0));
	free(ft_alloc_list(1));
	if (state == 0)
		exit(0);
	exit(1);
}

t_list	**ft_alloc_list(int list_num)
{
	static	t_list	**(ptr[2]);

	if (ptr[list_num] == NULL)
	{
		ptr[list_num] = malloc(sizeof(t_list *));
		if (!ptr[list_num])
			exit(1);
		*(ptr[list_num]) = NULL;
	}
	return (ptr[list_num]);
}

void	*ft_malloc(size_t size, int list_num)
{
	void	*ptr;
	t_list	**list;

	list = ft_alloc_list(list_num);
	ptr = malloc(size);
	if (!ptr)
		return (ft_lstclear(list, &ft_delete), NULL);
	ft_add_address(ptr, list_num);
	return (ptr);
}
