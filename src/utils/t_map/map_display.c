/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:32:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/03 10:48:10 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	display_map(t_map *map, int display_link)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map;
		if (display_link)
			ft_printf("ACTUAL,LEFT,RIGHT,UPPER,BELOW\n");
		while (tmp)
		{
			if (display_link)
				ft_printf("%s,%s,%s,%s,%s  ", tmp->slot, tmp->left, tmp->right->slot, tmp->upper, tmp->below);
			else
				ft_printf("%s ", tmp->slot);
			tmp = tmp->right;
		}
		ft_printf("\n");
		map = map->below;
	}
}
