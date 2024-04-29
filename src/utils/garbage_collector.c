/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 07:56:02 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/29 15:19:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

// Add free option for a chained list so
// all the chain can be free instead of just one element
t_garbage	*new_garbage(void *ptr)
{
	t_garbage	*garbage;

	garbage = malloc(sizeof(t_garbage));
	if (!garbage)
	{
		free(ptr);
		raise_error(MALLOC_ERROR);
	}
	garbage->content = ptr;
	garbage->next = NULL;
	return (garbage);
}

void	add_garbage(t_garbage **garbage, void *ptr)
{
	t_garbage	*new;
	t_garbage	*tmp;

	if (!*garbage)
	{
		*garbage = new_garbage(ptr);
		return ;
	}
	new = new_garbage(ptr);
	tmp = *garbage;
	while (tmp->next)
	{
		if (tmp->content == ptr)
			return ;
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	clear_garbage(t_garbage **garbage)
{
	t_garbage	*next;

	if (!*garbage)
		return ;
	while (*garbage)
	{
		next = (*garbage)->next;
		free((*garbage)->content);
		(*garbage)->content = NULL;
		free(*garbage);
		*garbage = next;
	}
	*garbage = NULL;
}

void	delete_garbage(t_garbage **garbage, void *ptr)
{
	t_garbage	*tmp;
	t_garbage	*prev;

	tmp = *garbage;
	prev = NULL;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*garbage = tmp->next;
			free(tmp->content);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	garbage_collector(t_garbage_action action, void *ptr)
{
	static t_garbage	*garbage = NULL;

	if (action == ADD)
		add_garbage(&garbage, ptr);
	else if (action == DELETE)
		delete_garbage(&garbage, ptr);
	else if (action == CLEAR)
		clear_garbage(&garbage);
}
