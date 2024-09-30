/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <namoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:02:37 by namoussa          #+#    #+#             */
/*   Updated: 2023/11/17 15:23:33 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	my_spar(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

char	*strnstr_helper(size_t *i, size_t *j, char *c1, char *to_find)
{
	while (c1[*i] && to_find[*j] && c1[*i] == to_find[*j])
	{
		*i += 1;
		*j += 1;
	}
	if (to_find[*j] == '\0' && (!ft_isalpha(c1[*i]) || c1[*i] == '\0'))
		return (&c1[*i - *j]);
	return (NULL);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	char	*c1;
	char	*to_find;
	size_t	i;
	size_t	j;
	size_t	temp_i;

	c1 = ft_strtrim(s1, " ");
	to_find = ft_strtrim(s2, " ");
	if (to_find[0] == '\0')
		return (c1);
	i = 0;
	while (c1[i] && i < len)
	{
		j = 0;
		if (c1[i] == to_find[0])
		{
			temp_i = i;
			if (strnstr_helper(&temp_i, &j, c1, to_find))
				return (&c1[i]);
		}
		i++;
	}
	return (NULL);
}
