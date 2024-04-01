/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 07:56:02 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/01 10:51:30 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_garbage	*new_garbage(void *ptr)
{
	t_garbage	*garbage;

	garbage = malloc(sizeof(t_garbage));
	if (!garbage)
	{
		free(ptr);
		ft_error(MALLOC_ERROR);
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
	t_garbage	*tmp;
	t_garbage	*next;

	if (!*garbage)
		return ;
	tmp = *garbage;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = next;
	}
	*garbage = NULL;
}

void	delete_garbage(t_garbage **garbage, void *ptr)
{
	t_garbage	*tmp;
	t_garbage	*to_free;

	if (!*garbage || !ptr)
		return ;
	tmp = *garbage;
	while (tmp->next)
	{
		if (tmp->next->content == ptr)
		{
			to_free = tmp->next;
			tmp->next = tmp->next->next;
			free(to_free->content);
			to_free->content = NULL;
			free(to_free);
		}
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
