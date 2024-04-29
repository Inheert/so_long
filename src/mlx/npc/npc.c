/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:38:39 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/29 14:09:32 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	*initialize_npc_hooks(void *param)
{
	t_player	*npc;

	npc = (t_player *)param;
	if (!npc)
		return (NULL);
	mlx_loop_hook(npc->mlx, &player_animation, npc);
	mlx_loop_hook(npc->mlx, &npc_movement, npc);
	return (NULL);
}

void	*initialize_npc_components(t_player *npc)
{
	pthread_t	tid;

	npc->health = NPC_HEALTH;
	npc->on_remove = false;
	npc->idle_sprites = create_animation_chain(
			npc, true, S_HANDGUN_IDLE_PATH, S_HANDGUN_IDLE_COUNT, IDLE);
	npc->walking_sprites = create_animation_chain(
			npc, true, S_HANDGUN_WALK_PATH, S_HANDGUN_WALK_COUNT, WALK);
	npc->shoot_sprites = create_animation_chain(
			npc, false, S_HANDGUN_SHOOT_PATH, S_HANDGUN_SHOOT_COUNT, SHOOT);
	npc->melee_sprites = create_animation_chain(
			npc, false, S_HANDGUN_MELEE_PATH, S_HANDGUN_MELEE_COUNT, MELEE);
	create_player_collision(npc);

	pthread_create(&tid, NULL, initialize_npc_hooks, npc);
	pthread_detach(tid);
	return (NULL);
}

t_player	*init_npc(mlx_t *mlx, t_map *pos)
{
	t_player		*npc;
	mlx_texture_t	*texture;

	if (!mlx || !pos)
		raise_error(NPC_CREATION_ERROR);
	texture = mlx_load_png(
			"./src/textures/player/handgun/idle/survivor-idle_handgun_0.png");
	if (!texture)
		return (raise_error(MLX_TEXTURE_ERROR), close_mlx(NULL), NULL);
	npc = ft_malloc(sizeof(t_player), 1);
	npc->mlx = mlx;
	npc->pos = pos;
	npc->img = mlx_texture_to_image(mlx, texture);
	if (!npc->img)
		return (raise_error(MLX_IMG_ERROR), close_mlx(NULL), NULL);
	if (!mlx_resize_image(npc->img,
			MLX_WIN_HEIGHT / PLAYER_SIZE_DIV, MLX_WIN_HEIGHT / PLAYER_SIZE_DIV))
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	if (mlx_image_to_window(mlx, npc->img, pos->x, pos->y))
		return (raise_error(MLX_IMG_ERROR), close_mlx(NULL), NULL);
	npc->img->enabled = false;
	initialize_npc_components(npc);
	return (npc);
}

void	init_all_npcs(mlx_t *mlx, t_map *map, t_player *player)
{
	t_map		**npcs;
	t_player	*npc;
	uint32_t	i;

	if (!mlx || !map || !player)
		return ;
	npcs = find_symbols(map, 'C');
	i = 0;
	while (npcs[i])
		i++;
	player->ennemies = ft_malloc(sizeof(t_player), i + 1);
	i = 0;
	while (npcs[i])
	{
		npc = init_npc(mlx, npcs[i]);
		if (!npc)
			return ;
		player->ennemies[i] = npc;
		npc->ennemies = ft_malloc(sizeof(t_player), i + 1);
		npc->ennemies[0] = player;
		i++;
	}
	garbage_collector(DELETE, npcs);
}
