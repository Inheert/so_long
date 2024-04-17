/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moover.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:23:45 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/17 18:03:24 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

bool	predict_player_pos(t_player	*player, int x, int y)
{
	mlx_image_t			*ply_collision;

	ply_collision = player->collision->img;
	if (x == -1 && player->pos->left->slot[0] == '1')
	{
		if (ply_collision->instances[0].x - PLAYER_SPEED  <= player->pos->left->img->instances[0].x + (int32_t)player->pos->left->img->width)
			return (false);
	}
	else if (x == 1 && player->pos->right->slot[0] == '1')
	{
		if (ply_collision->instances[0].x + (int32_t)ply_collision->width + PLAYER_SPEED  >= player->pos->right->img->instances[0].x)
			return (false);
	}
	if (y == -1 && player->pos->upper->slot[0] == '1')
	{
		if (ply_collision->instances[0].y - PLAYER_SPEED  <= player->pos->upper->img->instances[0].y + (int32_t)player->pos->left->img->height)
			return (false);
	}
	else if (y == 1 && player->pos->below->slot[0] == '1')
	{
		if (ply_collision->instances[0].y + (int32_t)ply_collision->height + PLAYER_SPEED  >= player->pos->below->img->instances[0].y)
			return (false);
	}


	player->pos->img->enabled = true;
	if (y == 1)
	{
		if (ply_collision->instances[0].y + PLAYER_SPEED - player->pos->img->instances[0].y >= (int32_t)player->pos->img->height / 2)
			player->pos = player->pos->below;
	}
	else if (y == -1)
	{
		if (player->pos->img->instances[0].y - ply_collision->instances[0].y + PLAYER_SPEED >= (int32_t)player->pos->img->height / 2)
			player->pos = player->pos->upper;
	}
	if (x == 1)
	{
		if (ply_collision->instances[0].x + PLAYER_SPEED - player->pos->img->instances[0].x >= (int32_t)player->pos->img->width / 2)
			player->pos = player->pos->right;
	}
	else if (x == -1)
	{
		if (player->pos->img->instances[0].x - ply_collision->instances[0].x + PLAYER_SPEED >= (int32_t)player->pos->img->width / 2)
			player->pos = player->pos->left;
	}
	player->pos->img->enabled = false;
	return (true);
}

void	move_player(t_player *player, int x, int y)
{
	if (!predict_player_pos(player, x, y))
	{
		printf("Wall collide\n");
		return ;
	}
	printf("All good\n");
	player->collision->img->instances[0].x += x * PLAYER_SPEED;
	player->collision->img->instances[0].y += y * PLAYER_SPEED;
	player->img->instances[0].x += x * PLAYER_SPEED;
	player->img->instances[0].y += y * PLAYER_SPEED;
}

void	player_movement(void *param)
{
	static mlx_t	*mlx = NULL;
	t_player	*player;

	player = (t_player *)param;
	if (!player)
		return ;
	if (!mlx)
		mlx = player->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(player, 0, -1);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_player(player, 0, 1);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(player, -1, 0);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(player, 1, 0);
}
