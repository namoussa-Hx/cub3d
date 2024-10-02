/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <namoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:51:26 by namoussa          #+#    #+#             */
/*   Updated: 2023/11/05 15:47:00 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isdigit(char *c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (c == NULL)
		return (0);
	str = ft_strtrim(c, " ");
	if (str == NULL)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] == '0')
		i++;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n' && (str[i] >= '0' && str[i] <= '9'))
	{
		j++;
		i++;
	}
	if (str[i] == '\0' && j <= 10)
		return (1);
	return (0);
}
