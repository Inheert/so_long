/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:16 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/09 09:06:22 by tclaereb         ###   ########.fr       */
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
		sprite->prev = NULL;
		mlx_delete_image(mlx, tmp->img);
	}
}

void	remove_sprites(t_player *ent)
{
	if (!ent->mlx)
		return ;
	if (ent->current_sprites)
	{
		remove_sprite(ent->mlx, ent->current_sprites);
		ent->current_sprites = NULL;
	}
	if (!ent->walking_sprites)
	{
		remove_sprite(ent->mlx, ent->walking_sprites);
		garbage_collector(DELETE, ent->walking_sprites);
		ent->walking_sprites = NULL;
	}
	if (!ent->idle_sprites)
	{
		remove_sprite(ent->mlx, ent->idle_sprites);
		garbage_collector(DELETE, ent->idle_sprites);
		ent->idle_sprites = NULL;
	}
	if (!ent->shoot_sprites)
	{
		remove_sprite(ent->mlx, ent->shoot_sprites);
		garbage_collector(DELETE, ent->shoot_sprites);
		ent->shoot_sprites = NULL;
	}
	if (!ent->reload_sprites)
	{
		remove_sprite(ent->mlx, ent->reload_sprites);
		garbage_collector(DELETE, ent->reload_sprites);
		ent->reload_sprites = NULL;
	}
	if (!ent->melee_sprites)
	{
		remove_sprite(ent->mlx, ent->melee_sprites);
		garbage_collector(DELETE, ent->melee_sprites);
		ent->melee_sprites = NULL;
	}
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
	remove_sprites(ent);
	remove_hitbox(ent);
	ent->already_remove = true;
	//garbage_collector(DELETE, ent);
}

