/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moover.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:23:45 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/18 15:14:52 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	actualize_player_map_pos(t_player *player, int x, int y, int speed)
{
	mlx_image_t			*ply_collision;

	ply_collision = player->collision->img;
	player->pos->img->enabled = true;
	if (y == 1 && player->pos->below)
	{
		if (ply_collision->instances[0].y + speed - player->pos->img->instances[0].y >= (int32_t)player->pos->img->height / 2)
			player->pos = player->pos->below;
	}
	else if (y == -1 && player->pos->upper)
	{
		if (player->pos->img->instances[0].y - ply_collision->instances[0].y + speed >= (int32_t)player->pos->img->height / 2)
			player->pos = player->pos->upper;
	}
	if (x == 1 && player->pos->right)
	{
		if (ply_collision->instances[0].x + speed - player->pos->img->instances[0].x >= (int32_t)player->pos->img->width / 2)
			player->pos = player->pos->right;
	}
	else if (x == -1 && player->pos->left)
	{
		if (player->pos->img->instances[0].x - ply_collision->instances[0].x + speed >= (int32_t)player->pos->img->width / 2)
			player->pos = player->pos->left;
	}
	player->pos->img->enabled = false;
}

bool	predict_player_pos(t_player	*player, int x, int y, int speed)
{
	mlx_image_t			*ply_collision;

	ply_collision = player->collision->img;
	if (x == -1 && player->pos->left->slot[0] == '1')
	{
		if (ply_collision->instances[0].x - speed  <= player->pos->left->img->instances[0].x + (int32_t)player->pos->left->img->width)
			return (false);
	}
	else if (x == 1 && player->pos->right->slot[0] == '1')
	{
		if (ply_collision->instances[0].x + (int32_t)ply_collision->width + speed  >= player->pos->right->img->instances[0].x)
			return (false);
	}
	if (y == -1 && player->pos->upper->slot[0] == '1')
	{
		if (ply_collision->instances[0].y - speed  <= player->pos->upper->img->instances[0].y + (int32_t)player->pos->left->img->height)
			return (false);
	}
	else if (y == 1 && player->pos->below->slot[0] == '1')
	{
		if (ply_collision->instances[0].y + (int32_t)ply_collision->height + speed  >= player->pos->below->img->instances[0].y)
			return (false);
	}
	actualize_player_map_pos(player, x, y, speed);
	return (true);
}

void	move_player(t_player *player, int x, int y, bool double_input)
{
	int	speed;

	if (!player->is_moving)
	{
		player->current_sprites->img->enabled = false;
		player->current_sprites = player->shoot_sprites;
	}
	player->is_moving = true;
	speed = PLAYER_SPEED;
	if (speed > 30)
		speed = 30;
	if (double_input)
		speed /= 1.5;
	if (!predict_player_pos(player, x, y, speed))
		return ;
	player->collision->img->instances[0].x += x * speed;
	player->collision->img->instances[0].y += y * speed;
	player->img->instances[0].x += x * speed;
	player->img->instances[0].y += y * speed;
}

void	player_movement(void *param)
{
	static mlx_t	*mlx = NULL;
	t_player		*player;

	player = (t_player *)param;
	if (!player)
		return ;
	if (!mlx)
		mlx = player->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_W) && mlx_is_key_down(mlx, MLX_KEY_D))
		return (move_player(player, 1, -1, true));
	if (mlx_is_key_down(mlx, MLX_KEY_W) && mlx_is_key_down(mlx, MLX_KEY_A))
		return (move_player(player, -1, -1, true));
	if (mlx_is_key_down(mlx, MLX_KEY_S) && mlx_is_key_down(mlx, MLX_KEY_D))
		return (move_player(player, 1, 1, true));
	if (mlx_is_key_down(mlx, MLX_KEY_S) && mlx_is_key_down(mlx, MLX_KEY_A))
		return (move_player(player, -1, 1, true));
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		return (move_player(player, 0, -1, false));
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		return (move_player(player, 0, 1, false));
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		return (move_player(player, -1, 0, false));
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		return (move_player(player, 1, 0, false));
	if (player->is_moving)
	{
		player->current_sprites->img->enabled = false;
		player->current_sprites = player->idle_sprites;
		player->is_moving = false;
	}
}
