/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:35 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 17:48:01 by tclaereb         ###   ########.fr       */
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

void	*player_anim_thread(void *param)
{
	t_player		*player;

	player = (t_player *)param;
	pthread_mutex_lock(&player->anim_mutex);
	if (!player || player->on_remove)
		return (pthread_mutex_unlock(&player->anim_mutex), NULL);
	if (!player->current_sprites && player->idle_sprites)
		set_animation(player, player->idle_sprites, true);
	player->current_sprites->img->enabled = false;
	player->current_sprites = player->current_sprites->next;
	if (!player->current_sprites && player->idle_sprites)
		set_animation(player, player->idle_sprites, true);
	player->current_sprites->img->instances[0].x = player->img->instances[0].x;
	player->current_sprites->img->instances[0].y = player->img->instances[0].y;
	player->current_sprites->img->enabled = true;
	pthread_mutex_unlock(&player->anim_mutex);
	return (NULL);
}

void	player_animation(void *param)
{
	pthread_t		tid;

	if ((t_player *)param && ((t_player *)param)->on_remove)
		return ;
	pthread_create(&tid, NULL, player_anim_thread, param);
	pthread_join(tid, NULL);
}
