/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:35 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/18 15:27:15 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	set_animation()
{
	
}

void	player_animation(void *param)
{
	static mlx_t	*mlx = NULL;
	t_player		*player;

	player = (t_player *)param;
	if (!player)
		return ;
	if (!mlx)
		mlx = player->mlx;
	if (!player->current_sprites)
		player->current_sprites = player->idle_sprites;
	player->current_sprites->img->enabled = false;
	player->current_sprites = player->current_sprites->next;
	player->current_sprites->img->instances[0].x = player->img->instances[0].x;
	player->current_sprites->img->instances[0].y = player->img->instances[0].y;
	player->current_sprites->img->enabled = true;
}
