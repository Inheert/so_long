/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:26:22 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/16 16:34:50 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

t_map	*find_player_pos(t_map *map)
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
