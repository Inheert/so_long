/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_link_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:09:07 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/03 10:27:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	map_link_lines(t_map *first_line, t_map *second_line)
{
	while (first_line && second_line)
	{
		map_add_below(&first_line, second_line);
		first_line = first_line->right;
		second_line = second_line->right;
	}
}
