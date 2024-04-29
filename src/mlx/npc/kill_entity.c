/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:16 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/29 15:22:33 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	remove_sprite(mlx_t *mlx, t_sprites *sprite)
{
	t_sprites	*tmp;

	if (!sprite || !mlx)
		return ;
	while (sprite)
	{
		tmp = sprite;
		sprite = sprite->next;
		mlx_delete_image(mlx, tmp->img);
	}
}

void	remove_sprites(t_player *ent)
{
	if (!ent)
		return ;
	remove_sprite(ent->mlx, ent->current_sprites);
	remove_sprite(ent->mlx, ent->walking_sprites);
	garbage_collector(DELETE, ent->walking_sprites);
	remove_sprite(ent->mlx, ent->idle_sprites);
	garbage_collector(DELETE, ent->idle_sprites);
	remove_sprite(ent->mlx, ent->shoot_sprites);
	garbage_collector(DELETE, ent->shoot_sprites);
	remove_sprite(ent->mlx, ent->reload_sprites);
	garbage_collector(DELETE, ent->reload_sprites);
	remove_sprite(ent->mlx, ent->melee_sprites);
	garbage_collector(DELETE, ent->melee_sprites);
}

void	kill_entity(t_player *ent, t_player *killer)
{
	int	i;
	int	find;

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
	remove_sprites(ent);
	garbage_collector(DELETE, ent);
}
