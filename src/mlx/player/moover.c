/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moover.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:23:45 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/28 09:41:53 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	actualize_player_map_pos(t_player *player, int x, int y, int speed)
{
	mlx_image_t			*ply_collision;

	ply_collision = player->collision->img;
	if (y == 1 && player->pos->below)
	{
		if (ply_collision->instances[0].y + speed
			- player->pos->img->instances[0].y
			>= (int32_t)player->pos->img->height / 2)
			player->pos = player->pos->below;
	}
	else if (y == -1 && player->pos->upper)
	{
		if (player->pos->img->instances[0].y - ply_collision->instances[0].y
			+ speed >= (int32_t)player->pos->img->height / 2)
			player->pos = player->pos->upper;
	}
	if (x == 1 && player->pos->right)
	{
		if (ply_collision->instances[0].x + speed
			- player->pos->img->instances[0].x
			>= (int32_t)player->pos->img->width / 2)
			player->pos = player->pos->right;
	}
	else if (x == -1 && player->pos->left)
	{
		if (player->pos->img->instances[0].x - ply_collision->instances[0].x
			+ speed >= (int32_t)player->pos->img->width / 2)
			player->pos = player->pos->left;
	}
}

bool	predict_player_pos(t_player	*player, int x, int y, int speed)
{
	mlx_image_t			*ply_collision;

	ply_collision = player->collision->img;
	if (x == -1 && player->pos->left->slot[0] == '1')
	{
		if (ply_collision->instances[0].x - speed
			<= player->pos->left->img->instances[0].x
			+ (int32_t)player->pos->left->img->width)
			return (false);
	}
	else if (x == 1 && player->pos->right->slot[0] == '1')
	{
		if (ply_collision->instances[0].x + (int32_t)ply_collision->width
			+ speed >= player->pos->right->img->instances[0].x)
			return (false);
	}
	if (y == -1 && player->pos->upper->slot[0] == '1')
	{
		if (ply_collision->instances[0].y - speed
			<= player->pos->upper->img->instances[0].y
			+ (int32_t)player->pos->left->img->height)
			return (false);
	}
	else if (y == 1 && player->pos->below->slot[0] == '1')
	{
		if (ply_collision->instances[0].y + (int32_t)ply_collision->height
			+ speed >= player->pos->below->img->instances[0].y)
			return (false);
	}
	actualize_player_map_pos(player, x, y, speed);
	return (true);
}

void	move_player(t_player *player, int x, int y, bool *input_pressed)
{
	int	speed;
	int	add_x;
	int	add_y;

	*input_pressed = true;
	set_animation(player, player->walking_sprites, false);
	if (mlx_is_key_down(player->mlx, MLX_KEY_LEFT_SHIFT))
		speed = PLAYER_RUN_SPEED * player->mlx->delta_time;
	else
		speed = PLAYER_WALK_SPEED * player->mlx->delta_time;
	if (!predict_player_pos(player, x, y, speed))
		return ;
	add_x = x * speed;
	add_y = y * speed;
	player->collision->img->instances[0].x += add_x;
	player->collision->img->instances[0].y += add_y;
	player->collision->x_pivot += add_x;
	player->collision->y_pivot += add_y;
	player->img->instances[0].x += add_x;
	player->img->instances[0].y += add_y;
}

void	player_movement(void *param)
{
	static mlx_t	*mlx = NULL;
	t_player		*player;
	bool			input_pressed;

	input_pressed = false;
	player = (t_player *)param;
	if (!player)
		return ;
	if (!mlx)
		mlx = player->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(player, 0, -1, &input_pressed);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_player(player, 0, 1, &input_pressed);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(player, -1, 0, &input_pressed);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(player, 1, 0, &input_pressed);
	if (!input_pressed)
		remove_animation(player, player->walking_sprites);
}
