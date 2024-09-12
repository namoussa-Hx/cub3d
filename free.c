#include "cub3d.h"

t_free	*newnode(void *address)
{
	t_free	*new;

	new = (t_free *)malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	new->addr = address;
	new->next = NULL;
	return (new);
}

void	addback(t_free **lst, t_free *new)
{
	t_free	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	free_all(t_free **lst)
{
	t_free *temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp->addr);
		free(temp);
	}
}