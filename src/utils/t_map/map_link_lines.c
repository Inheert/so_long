/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_link_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:09:07 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/08 10:12:10 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	map_link_lines(t_map *first_line, t_map *second_line)
{
	if (!first_line && !second_line)
		return ;
	else if (!first_line)
		first_line = second_line->upper;
	else if (!second_line)
		second_line = first_line->below;
	while (first_line && second_line)
	{
		map_add_below(&first_line, second_line);
		first_line = first_line->right;
		second_line = second_line->right;
	}
}
