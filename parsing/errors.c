/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:41:25 by namoussa          #+#    #+#             */
/*   Updated: 2024/08/29 13:41:26 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	my_strchr(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(c, str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_extension(char *file)
{
	char	*ext;
	int		res;

	ext = ft_strchr(file, '.');
	res = ft_strcmp(ext, ".cub");
	if (ext == NULL || res != 0)
		return (1);
	if (check_head_file(file))
		return (1);
	return (0);
}

int	check_conditions(char ch, int count)
{
	if ((ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W') && count > 1)
		return (1);
	return (0);
}

int	check_valid_char(char c, int flag)
{
	if (flag == 1)
	{
		if (c == '\0' || c == 10 || (c >= 9 && c <= 13) || c == 32)
			return (1);
	}
	if (flag == 2)
	{
		if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			return (1);
	}
	return (0);
}
