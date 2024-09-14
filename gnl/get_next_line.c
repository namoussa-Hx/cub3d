/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:40:42 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/14 19:14:19 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buffer;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0
		|| BUFFER_SIZE > 2147483647)
		return (temp = NULL, NULL);
	buffer = (char *)ft_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (temp = NULL, NULL);
	while (1)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buffer[i] = '\0';
		temp = ft_strjoin_gnl(temp, buffer);
		if (!temp)
			return (NULL);
		if (check_line(temp))
			break ;
	}
	return (print_line(&temp));
}
