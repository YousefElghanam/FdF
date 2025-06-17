/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:06:43 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/15 22:08:15 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delete(void *ptr)
{
	free(ptr);
}

void	return_error(int state, ...)
{
	t_list	**list;

	list = ft_alloc_list();
	if (state == 0)
		;
	else if (state == 1)
		write(2, "Error\n", 6);
	else if (state == 2)
		write(1, "KO\n", 3);
	ft_lstclear(list, &ft_delete);
	free(list);
	exit(1);
}

t_list	**ft_alloc_list(void)
{
	static t_list	**ptr;

	if (ptr == NULL)
	{
		ptr = malloc(sizeof(t_list *));
		if (!ptr)
			exit(1);
		*ptr = NULL;
	}
	return (ptr);
}

void	ft_add_address(void *ptr)
{
	void	*node;
	t_list	**list;

	list = ft_alloc_list();
	node = ft_lstnew(ptr);
	if (!node)
	{
		ft_lstclear(list, &ft_delete);
		return_error(1);
	}
	ft_lstadd_back(list, node);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	t_list	**list;

	list = ft_alloc_list();
	ptr = malloc(size);
	if (!ptr)
		return (ft_lstclear(list, &ft_delete), NULL);
	ft_add_address(ptr);
	return (ptr);
}
