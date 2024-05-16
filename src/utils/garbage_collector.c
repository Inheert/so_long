/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 07:56:02 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 13:36:00 by tclaereb         ###   ########.fr       */
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
		raise_error(MALLOC_ERROR, NULL);
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

void	clear_garbage(mlx_t *mlx, t_garbage **garbage, t_garbage **texture_garbage, t_garbage **img_garbage)
{
	t_garbage	*next;

	if (*garbage)
	{
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
	if (*texture_garbage)
	{
		while (*texture_garbage)
		{
			next = (*texture_garbage)->next;
			mlx_delete_texture((*texture_garbage)->content);
			(*texture_garbage)->content = NULL;
			free(*texture_garbage);
			*texture_garbage = next;
		}
		*texture_garbage = NULL;
	}
	if (*img_garbage && mlx)
	{
		while (*img_garbage)
		{
			next = (*img_garbage)->next;
			mlx_delete_image(mlx, (*img_garbage)->content);
			(*img_garbage)->content = NULL;
			free(*img_garbage);
			*img_garbage = next;
		}
		*img_garbage = NULL;
	}
}

void	delete_garbage(t_garbage **garbage, void *ptr)
{
	t_garbage	*tmp;
	t_garbage	*prev;

	if (!*garbage || !ptr)
		return ;
	tmp = *garbage;
	prev = NULL;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			if (prev && tmp->next)
				prev->next = tmp->next;
			else if (prev && !tmp->next)
				prev->next = NULL;
			else
				*garbage = tmp->next;
			free(tmp->content);
			tmp->content = NULL;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void display_garbage(t_garbage *garbage)
{
	t_garbage	*tmp;

	tmp = garbage;
	while (tmp)
	{
		printf("%p\n", tmp->content);
		tmp = tmp->next;
	}
}

void	garbage_collector(t_garbage_action action, void *ptr)
{
	static mlx_t		*mlx = NULL;
	static t_garbage	*garbage = NULL;
	static t_garbage	*texture_garbage = NULL;
	static t_garbage	*img_garbage = NULL;

	if (action == INIT)
		mlx = (mlx_t *)ptr;
	else if (action == ADD)
		add_garbage(&garbage, ptr);
	else if (action == ADD_TEXTURE)
		add_garbage(&texture_garbage, ptr);
	else if (action == ADD_IMG)
		add_garbage(&img_garbage, ptr);
	else if (action == DELETE)
		delete_garbage(&garbage, ptr);
	else if (action == CLEAR)
		clear_garbage(mlx, &garbage, &texture_garbage, &img_garbage);
	else if (action == DISPLAY)
		display_garbage(garbage);
}
