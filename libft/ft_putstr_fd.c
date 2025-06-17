/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 23:56:06 by josefelghna       #+#    #+#             */
/*   Updated: 2025/05/12 12:29:23 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = 0;
	if (fd < 0)
		return (0);
	while (s[len])
		len++;
	write(fd, s, len);
	return (len);
}

// #include <fcntl.h>
// int main(void)
// {
// 	int fd;

// 	fd = open("test", O_RDWR);
// 	ft_putstr_fd("", fd);
// 	return (0);
// }