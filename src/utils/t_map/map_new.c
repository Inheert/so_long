/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:03:28 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 13:36:10 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

t_map	*map_new(char slot[2])
{
	t_map	*map;

	if (!slot)
		return (NULL);
	map = (t_map *)ft_malloc(sizeof(t_map), 1);
	map->slot[1] = '\0';
	if (slot[1] == '\n')
		slot[1] = '\0';
	if (!is_valid_symbol(slot))
		raise_error(UNKNOW_MAP_SYMBOL, NULL);
	ft_memcpy(map->slot, slot, 2);
	map->left = NULL;
	map->right = NULL;
	map->upper = NULL;
	map->below = NULL;
	return (map);
}
