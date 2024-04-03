/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:08:59 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/03 11:16:18 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

int	is_wall_valid(t_map *map)
{
	t_map	*tmp;

	while (map->upper)
		map = map->upper;
	tmp = map;
	while (tmp->right)
	{
		if (tmp->slot[0] != '1')
			return (0);
		tmp = tmp->right;
	}
	while (tmp->below)
	{
		if (tmp->slot[0] != '1')
			return (0);
		tmp = tmp->below;
	}
	while (tmp->left)
	{
		if (tmp->slot[0] != '1')
			return (0);
		tmp = tmp->left;
	}
	while (tmp->upper)
	{
		if (tmp->slot[0] != '1')
			return (0);
		tmp = tmp->upper;
	}
	return (1);
}
