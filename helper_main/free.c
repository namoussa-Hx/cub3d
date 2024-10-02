/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:09:07 by namoussa          #+#    #+#             */
/*   Updated: 2024/09/14 19:19:57 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_save	**save_add(void)
{
	static t_save	*save;

	if (save == NULL)
	{
		save = malloc(sizeof(t_save));
		if (!save)
			return (NULL);
		save->add = NULL;
		save->next = NULL;
	}
	return (&save);
}

void	*ft_malloc(size_t size)
{
	void	*add;
	t_save	*head;

	add = malloc(size);
	if (!add)
		return (0);
	head = malloc(sizeof(t_save));
	if (!head)
		return (0);
	head->add = add;
	head->next = *save_add();
	*save_add() = head;
	return (add);
}

int	is_ft_malloc_ptr(void *ptr)
{
	t_save	*head;

	head = *save_add();
	while (head)
	{
		if (head->add == ptr)
			return (1);
		head = head->next;
	}
	return (0);
}

void	free_all(void)
{
	t_save	*head;
	t_save	*temp;
	int		i;

	i = 0;
	head = *save_add();
	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->add)
			free(temp->add);
		free(temp);
		i++;
	}
}

int	_r(int fd1)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd1);
		if (line == NULL)
			break ;
		if (is_expect(line) == 1)
		{
			close(fd1);
			return (1);
		}
	}
	close(fd1);
	return (0);
}
