/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_symbol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:46:22 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/29 10:36:21 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

unsigned int	count_symbol(t_map *map, char c)
{
	t_map			*tmp;
	unsigned int	count;

	tmp = map;
	count = 0;
	while (map)
	{
		tmp = map;
		while (tmp)
		{
			if (tmp->slot[0] == c)
				count++;
			tmp = tmp->right;
		}
		map = map->below;
	}
	return (count);
}

t_map	**find_symbols(t_map *map, char c)
{
	t_map			**lst;
	t_map			*tmp;
	unsigned int	size;
	unsigned int 	i;

	i = 0;
	size = count_symbol(map, c);
	lst = ft_malloc(sizeof(t_map *), size + 1);
	tmp = map;
	while (map)
	{
		tmp = map;
		while (tmp)
		{
			if (tmp->slot[0] == c)
				lst[i++] = tmp;
			tmp = tmp->right;
		}
		map = map->below;
	}
	return (lst);
}
