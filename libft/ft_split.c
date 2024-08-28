/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <namoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:23:21 by namoussa          #+#    #+#             */
/*   Updated: 2023/11/17 17:34:03 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int include_digit(const char *s, char c)
{
	size_t i;
	int flag;

	i = 0;
	flag = 0;
	while (s[i] != '\0' && s[i] != '\n' && s[i] != c)
	{
		if (s[i] >= '0' && s[i] <= '9')
			flag++;
		i++;
	}
	if (flag == 0)
		return (1);
	return (0);
}

size_t	count_strings(const char *s, char c)
{
	size_t	nb_strings;
	int i;

	nb_strings = 0;
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		if (s[i] != c)
		{
			if(include_digit(s + i, c))
			 		return (0);
			while (s[i] != '\0' && s[i] != '\n' && s[i] != c)
				i++;
			nb_strings++;
			continue ;
		}
		i++;
	}
	return (nb_strings);
}


const char	*dup_word(char **dest, const char *src, char c)
{
	size_t	len;
	size_t	i;

	while (*src == c)
		src++;
	len = 0;
	while (src[len] != '\0' && src[len] != '\n' && src[len] != c)
		len++;
	if (len == 0)
		return (NULL);
	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (*dest == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		(*dest)[i] = src[i];
		i++;
	}
	(*dest)[i] = '\0';
	src += len;
	if (*src == c)
		src++;
	return (src);
}


void	free_strs(char ***strs, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free((*strs)[i]);
		i++;
	}
	free(*strs);
	*strs = NULL;
}

char	**ft_split(const char *s, char c)
{
	char	**strs;
	size_t	nbr_strings;
	size_t	i;

	if (s == NULL)
		return (NULL);
	nbr_strings = count_strings(s, c);
	if(nbr_strings != 3)
	    return (NULL);
	strs = (char **)malloc(sizeof(char *) * (nbr_strings + 1));
	if (strs != NULL)
	{
		strs[nbr_strings] = NULL;
		i = 0;
		while (i < nbr_strings)
		{
			s = dup_word(strs + i, s, c);
			if (s == NULL)
			{
				free_strs(&strs, i);
				return (NULL);
			}
			i++;
		}
	}
	return (strs);
}
