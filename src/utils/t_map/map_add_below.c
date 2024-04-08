/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_add_below.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:06:52 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/08 10:10:58 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	map_add_below(t_map **map, t_map *new)
{
	t_map	*tmp;

	if (!new)
		return ;
	if (!*map)
	{
		*map = new;
		return ;
	}
	tmp = *map;
	while (tmp->below)
	{
		tmp = tmp->below;
	}
	tmp->below = new;
	new->upper = tmp;
}
