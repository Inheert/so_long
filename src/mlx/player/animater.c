/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:35 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/28 09:49:47 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	set_animation(t_player *player, t_sprites *sprites, bool force)
{
	if (!player || !sprites)
		return ;
	if (player->current_sprites
		&& ((player->current_sprites->type == sprites->type && !force)
			|| (player->current_sprites->type == SHOOT)))
		return ;
	if (player->current_sprites)
		player->current_sprites->img->enabled = false;
	player->current_sprites = sprites;
}

void	remove_animation(t_player *player, t_sprites *sprites)
{
	if (!player || !sprites)
		return ;
	if (player->current_sprites
		&& player->current_sprites->type == sprites->type)
	{
		player->current_sprites->img->enabled = false;
		player->current_sprites = NULL;
	}
}

void	player_animation(void *param)
{
	static mlx_t	*mlx = NULL;
	static double	time = 0;
	t_player		*player;

	player = (t_player *)param;
	if (!player)
		return ;
	if (!mlx)
		mlx = player->mlx;
	if (!player->current_sprites)
		set_animation(player, player->idle_sprites, true);
	player->current_sprites->img->enabled = false;
	if (time < SPRITES_FRAME_RATE_PER_SEC)
		time += mlx->delta_time;
	else
	{
		player->current_sprites = player->current_sprites->next;
		time = 0;
	}
	if (!player->current_sprites)
		set_animation(player, player->idle_sprites, true);
	player->current_sprites->img->instances[0].x = player->img->instances[0].x;
	player->current_sprites->img->instances[0].y = player->img->instances[0].y;
	player->current_sprites->img->enabled = true;
}
