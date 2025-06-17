/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:54:02 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/22 13:19:36 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;

// 	str = ft_strdup("hi, this is it !!!!");
// 	ft_memset(str, '2', 5);
// 	printf("%s", str);
// 	return (0);
// }