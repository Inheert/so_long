/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:31:30 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 13:20:37 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	*npc_shooter_thread(void *param)
{
	t_player	*npc;
	t_point		current_pos;
	t_point		ennemy_pos;

	npc = (t_player *)param;
	if (!npc || npc->on_remove)
		return (NULL);
	if (++(npc->npc_shoot_waited) < npc->npc_move_count)
		return (NULL);
	current_pos.x = npc->collision->img->instances[0].x;
	current_pos.y = npc->collision->img->instances[0].y;
	ennemy_pos.x = npc->ennemies[0]->collision->x_pivot;
	ennemy_pos.y = npc->ennemies[0]->collision->y_pivot;
	raycast(npc, current_pos, ennemy_pos, img_sharing(NULL));
	return (NULL);
}

void	npc_shooter(void *param)
{
	t_player		*npc;

	npc = (t_player *)param;
	if (!npc || ((t_player *)param)->on_remove || !npc->ennemies[0])
		return ;
	if (++(npc->npc_shoot_waited) < npc->npc_shoot_delay
		|| npc->ennemies[0]->on_remove)
		return ;
	npc->npc_shoot_delay = random_in_range(NPC_MAX_DELAY_BEFORE_SHOOT);
	npc->npc_shoot_waited = 0;
	npc->x_aiming = npc->ennemies[0]->collision->x_pivot;
	npc->y_aiming = npc->ennemies[0]->collision->y_pivot;
	shoot_bullet(npc);
}
