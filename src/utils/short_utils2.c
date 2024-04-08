/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:50:40 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/08 10:19:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_map	*get_start_pos(t_map *map)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map;
		while (tmp)
		{
			if (tmp->slot[0] == 'P')
				return (tmp);
			tmp = tmp->right;
		}
		map = map->below;
	}
	return (NULL);
}

void	link_copy(t_map *map)
{
	t_map	*tmp;
	t_map	*tmp2;

	while (map)
	{
		tmp = map;
		tmp2 = map->below;
		while (tmp && tmp2)
		{
			tmp->below = tmp2;
			tmp2->upper = tmp;
			tmp = tmp->right;
			tmp2 = tmp2->right;
		}
		map = map->below;
	}
}

t_map	*copy_map(t_map *map)
{
	t_map	*new_map;
	t_map	*new_map_tmp;
	t_map	*tmp;

	new_map = NULL;
	new_map_tmp = NULL;
	while (map)
	{
		if (!new_map)
			tmp = map;
		else
			tmp = map->right;
		while (tmp)
		{
			map_add_right(&new_map_tmp, map_new(tmp->slot));
			tmp = tmp->right;
		}
		if (!new_map)
			new_map = new_map_tmp;
		map = map->below;
		map_add_below(&new_map_tmp, map_new(map->slot));
		new_map_tmp = new_map_tmp->below;
	}
	link_copy(new_map);
	return (new_map);
}
