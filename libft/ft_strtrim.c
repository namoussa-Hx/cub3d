/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:26:05 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/14 19:14:59 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i] || c == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		f;
	int		l;
	int		i;

	f = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	while (s1[f] && check_set(s1[f], set))
		f++;
	l = ft_strlen(s1);
	while (l > f && check_set(s1[l - 1], set))
		l--;
	ptr = ft_malloc(sizeof(char) * (l - f) + 1);
	i = 0;
	if (!ptr)
		return (NULL);
	while (f < l)
		ptr[i++] = s1[f++];
	ptr[i] = '\0';
	return (ptr);
}

// int main ()
// {
// 	char str1[] = "   Hello World!   ";
// 	char str2[] = " ";
// 	char *result;
// 	result = ft_strtrim(str1, str2);
// 	printf("'%s'\n", result);
// 	free(result);
// 	return 0;
// }
