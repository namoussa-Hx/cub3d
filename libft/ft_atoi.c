/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <namoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:57:40 by namoussa          #+#    #+#             */
/*   Updated: 2023/11/17 15:48:59 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	long long	res;
	long long	negative;
	int			i;
	long long	ress;

	i = 0;
	if (str == NULL)
		return (-1);
	negative = 1;
	res = 0;
	while ((str[i] && str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		negative = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if(res > 2147483647 || res < -2147483648)
		return (-1);
	ress = (res * negative);
	return (ress);
}
/*int main ()
{
	char str[] = "------1234";
	printf ("%d",ft_atoi(str));
	return (0);
}*/