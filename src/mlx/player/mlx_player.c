/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:15:54 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/16 17:09:37 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	init_player(t_map *map)
{
	t_map	*pos;

	pos  = find_player_pos(map);
	if (!pos)
		raise_error(PLAYER_CREATION_ERROR);
	
}
