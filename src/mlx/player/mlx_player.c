/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:15:54 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/15 18:27:45 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	create_player_collision(t_player *player, t_map_info *map)
{
	uint32_t		x_pivot;
	uint32_t		y_pivot;
	t_collision		*collision;
	mlx_texture_t	*texture;

	x_pivot = player->img->instances[0].x + player->img->width / 2;
	y_pivot = player->img->instances[0].y + player->img->height / 2;
	collision = ft_malloc(sizeof(t_collision), 1);
	collision->x_pivot = x_pivot;
	collision->y_pivot = y_pivot;
	collision->x_1 = x_pivot - MLX_WIN_HEIGHT / map->map_width / 2;
	collision->y_1 = y_pivot - MLX_WIN_HEIGHT / map->map_height / 2;
	texture = mlx_load_png("./src/textures/hitboxview.png");
	if (!texture)
		return (raise_error(MLX_TEXTURE_ERROR), close_mlx(NULL));
	collision->img = mlx_texture_to_image(player->mlx, texture);
	if (!collision->img)
		return (raise_error(MLX_IMG_ERROR), close_mlx(NULL));
	if (!mlx_resize_image(collision->img,
			MLX_WIN_HEIGHT / map->map_width, MLX_WIN_HEIGHT / map->map_height)
		|| mlx_image_to_window(player->mlx, collision->img,
			collision->x_1, collision->y_1) == -1)
		return (mlx_close_window(player->mlx), raise_error(MLX_IMG_ERROR));
	garbage_collector(ADD_TEXTURE, texture);
	collision->img->enabled = SHOW_COLLISION_BOX;
	player->collision = collision;
}

void	initialize_player_components(t_player *player, t_map_info *map)
{
	player->health = PLAYER_HEALTH;
	player->can_dash = true;
	player->idle_sprites = create_animation_chain(
			player, map, true, S_HANDGUN_IDLE_PATH, S_HANDGUN_IDLE_COUNT, IDLE);
	player->walking_sprites = create_animation_chain(
			player, map, true, S_HANDGUN_WALK_PATH, S_HANDGUN_WALK_COUNT, WALK);
	player->shoot_sprites = create_animation_chain(
			player, map, false, S_HANDGUN_SHOOT_PATH, S_HANDGUN_SHOOT_COUNT, SHOOT);
	player->melee_sprites = create_animation_chain(
			player, map, false, S_HANDGUN_MELEE_PATH, S_HANDGUN_MELEE_COUNT, MELEE);
	create_player_collision(player, map);
	mlx_loop_hook(player->mlx, &player_movement, player);
	mlx_cursor_hook(player->mlx, &player_aiming, player);
	mlx_mouse_hook(player->mlx, &on_mouse_action, player);
	mlx_loop_hook(player->mlx, &player_animation, player);
}

t_player	*init_player(mlx_t *mlx, t_map_info *map)
{
	t_player		*player;
	t_map			*pos;
	mlx_texture_t	*texture;

	if (!mlx || !map || !map->map)
		raise_error(PLAYER_CREATION_ERROR);
	pos = find_player_pos(map->map);
	if (!pos)
		raise_error(PLAYER_CREATION_ERROR);
	texture = mlx_load_png(
			"./src/textures/player/handgun/idle/survivor-idle_handgun_0.png");
	if (!texture)
		return (raise_error(MLX_TEXTURE_ERROR), close_mlx(NULL), NULL);
	player = ft_malloc(sizeof(t_player), 1);
	player->mlx = mlx;
	player->pos = pos;
	player->img = mlx_texture_to_image(mlx, texture);
	if (!player->img)
		return (raise_error(MLX_IMG_ERROR), close_mlx(NULL), NULL);
	if (!mlx_resize_image(player->img,
			MLX_WIN_WIDTH / map->map_width, MLX_WIN_WIDTH / map->map_height))
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	if (mlx_image_to_window(mlx, player->img, pos->x, pos->y))
		return (raise_error(MLX_IMG_ERROR), close_mlx(NULL), NULL);
	garbage_collector(ADD_TEXTURE, texture);
	player->img->enabled = false;
	initialize_player_components(player, map);
	return (player);
}
