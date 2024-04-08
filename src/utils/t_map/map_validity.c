/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:08:59 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/08 10:20:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"


void	recursive_path_checker(t_map *map, int *is_path_valid)
{
	if (!map || *is_path_valid || map->slot[0] == '1')
		return ;
	else if (map->slot[0] == 'E')
	{
		*is_path_valid = 1;
		return ;
	}
	map->slot[0] = '1';
	recursive_path_checker(map->left, is_path_valid);
	recursive_path_checker(map->right, is_path_valid);
	recursive_path_checker(map->upper, is_path_valid);
	recursive_path_checker(map->below, is_path_valid);
}

int	is_valid_path_exist(t_map *map)
{
	t_map	*start_pos;
	int		is_path_valid;


	start_pos = get_start_pos(map);
	is_path_valid = 0;
	recursive_path_checker(start_pos, &is_path_valid);
	return (is_path_valid);
}

int	is_char_missing(t_map *map, t_map *tmp)
{
	t_check_symbols	check_symbols;

	tmp = map;
	check_symbols.is_exit_exist = 0;
	check_symbols.is_start_exist = 0;
	check_symbols.is_collectible_exist = 0;
	while (tmp)
	{
		if (tmp->slot[0] == 'E')
			check_symbols.is_exit_exist = 1;
		else if (tmp->slot[0] == 'P')
			check_symbols.is_start_exist = 1;
		else if (tmp->slot[0] == 'C')
			check_symbols.is_collectible_exist = 1;
		tmp = tmp->right;
		if (!tmp)
		{
			map = map->below;
			tmp = map;
		}
	}
	if (!check_symbols.is_exit_exist || !check_symbols.is_start_exist
		|| !check_symbols.is_collectible_exist)
		return (1);
	return (0);
}

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
