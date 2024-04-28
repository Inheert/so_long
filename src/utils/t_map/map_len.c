/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:56:04 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/28 09:23:49 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

int	*get_map_len(t_map *map)
{
	int		*map_len;
	t_map	*tmp;

	map_len = ft_malloc(sizeof(int), 2);
	tmp = map;
	while (tmp)
	{
		map_len[0]++;
		tmp = tmp->right;
	}
	tmp = map;
	while (tmp)
	{
		map_len[1]++;
		tmp = tmp->below;
	}
	return (map_len);
}
