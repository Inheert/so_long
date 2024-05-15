/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moover.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:45:11 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/15 16:34:40 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	*npc_movement_thread(void *param)
{
	t_player	*npc;
	int			add_x;
	int			add_y;

	npc = (t_player *)param;
	if (!npc || npc->on_remove)
		return (NULL);
	if (npc->npc_move_count >= NPC_TICK_BEFORE_MODIFY_MOVEMENT || npc->npc_move_count == 0)
	{
		npc->npc_move_x = rand() % 3 - 1;
		npc->npc_move_y = rand() % 3 - 1;
		npc->npc_move_count = 1;
	}
	npc->npc_move_count++;
	if (!predict_player_pos(npc, npc->npc_move_x, npc->npc_move_y, NPC_WALK_SPEED))
		return (NULL);
	add_x = npc->npc_move_x * NPC_WALK_SPEED;
	add_y = npc->npc_move_y * NPC_WALK_SPEED;
	npc->collision->img->instances[0].x += add_x;
	npc->collision->img->instances[0].y += add_y;
	npc->collision->x_pivot += add_x;
	npc->collision->y_pivot += add_y;
	npc->img->instances[0].x += add_x;
	npc->img->instances[0].y += add_y;
	if (npc->npc_move_x == 0 && npc->npc_move_y == 0)
		remove_animation(npc, npc->walking_sprites);
	return (NULL);
}

void	npc_movement(void *param)
{
	pthread_t		tid;

	if (!(t_player *)param || ((t_player *)param)->on_remove)
		return ;
	pthread_create(&tid, NULL, npc_movement_thread, param);
	pthread_detach(tid);
}
