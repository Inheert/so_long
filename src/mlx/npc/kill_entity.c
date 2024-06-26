/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:16 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 16:53:44 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	remove_sprite(mlx_t *mlx, t_sprites *sprite)
{
	t_sprites	*first;
	t_sprites	*tmp;
	int			i;

	if (!sprite || !mlx)
		return ;
	first = sprite;
	i = 0;
	while (sprite)
	{
		if (sprite == first && i++ != 0)
			break ;
		tmp = sprite;
		sprite = sprite->next;
		if (sprite)
			sprite->prev = NULL;
		mlx_delete_image(mlx, tmp->img);
	}
}

void	remove_sprites2(t_player *ent)
{
	if (!ent->mlx)
		return ;
	if (!ent->shoot_sprites)
	{
		remove_sprite(ent->mlx, ent->shoot_sprites);
		ent->shoot_sprites = NULL;
	}
	if (!ent->reload_sprites)
	{
		remove_sprite(ent->mlx, ent->reload_sprites);
		ent->reload_sprites = NULL;
	}
	if (!ent->melee_sprites)
	{
		remove_sprite(ent->mlx, ent->melee_sprites);
		ent->melee_sprites = NULL;
	}
}

void	remove_sprites(t_player *ent)
{
	if (!ent->mlx)
		return ;
	if (ent->current_sprites)
	{
		ent->current_sprites->img->enabled = false;
		ent->current_sprites = NULL;
	}
	if (!ent->walking_sprites)
	{
		remove_sprite(ent->mlx, ent->walking_sprites);
		ent->walking_sprites = NULL;
	}
	if (!ent->idle_sprites)
	{
		remove_sprite(ent->mlx, ent->idle_sprites);
		ent->idle_sprites = NULL;
	}
	remove_sprites2(ent);
}

void	remove_hitbox(t_player *ent)
{
	if (!ent)
		return ;
	mlx_delete_image(ent->mlx, ent->collision->img);
	garbage_collector(DELETE, ent->collision);
}

void	kill_entity(t_player *ent, t_player *killer)
{
	int		i;
	bool	find;

	if (!ent || !ent->mlx)
		return ;
	ent->on_remove = true;
	i = 0;
	find = false;
	while (killer->ennemies[i])
	{
		if (find)
		{
			killer->ennemies[i - 1] = killer->ennemies[i];
			killer->ennemies[i] = NULL;
		}
		if (killer->ennemies[i] == ent)
			find = true;
		i++;
	}
	if (killer->ennemies[i - 1] == ent)
		killer->ennemies[i - 1] = NULL;
	usleep(20000);
	pthread_mutex_lock(&ent->anim_mutex);
	remove_sprites(ent);
	remove_hitbox(ent);
	pthread_mutex_unlock(&ent->anim_mutex);
}
