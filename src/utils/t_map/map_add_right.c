/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_add_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:05:57 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/03 10:26:13 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	map_add_right(t_map **map, t_map *new)
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
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = new;
	new->left = tmp;
}
