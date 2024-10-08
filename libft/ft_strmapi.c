/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:42:52 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/14 19:14:56 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;
	int				len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = ft_malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (s && f)
	{
		while (s[i] != '\0')
		{
			str[i] = f(i, s[i]);
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
/*char	ft_toupperr(unsigned int c,char cc)
{
	if (cc >= 97 && cc <= 122)
		cc -= 32;
	return (cc);
}
int main ()
{
	char str[] = "hello";
	printf("%s",ft_strmapi(str,&ft_toupperr));
	return (0);
}*/
