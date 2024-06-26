/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moover.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:23:45 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 16:20:37 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	actualize_player_map_pos(t_player *player, int x, int y, int *speed)
{
	mlx_image_t			*ply_collision;

	ply_collision = player->collision->img;
	if (y == 1 && player->pos->below)
	{
		if (ply_collision->instances[0].y + *speed
			- player->pos->img->instances[0].y
			>= (int32_t)player->pos->img->height / 2)
			player->pos = player->pos->below;
	}
	else if (y == -1 && player->pos->upper)
	{
		if (player->pos->img->instances[0].y - ply_collision->instances[0].y
			+ *speed >= (int32_t)player->pos->img->height / 2)
			player->pos = player->pos->upper;
	}
	if (x == 1 && player->pos->right)
	{
		if (ply_collision->instances[0].x + *speed
			- player->pos->img->instances[0].x
			>= (int32_t)player->pos->img->width / 2)
			player->pos = player->pos->right;
	}
	else if (x == -1 && player->pos->left)
	{
		if (player->pos->img->instances[0].x - ply_collision->instances[0].x
			+ *speed >= (int32_t)player->pos->img->width / 2)
			player->pos = player->pos->left;
	}
}

void	is_player_in_vertex(t_player *player, int *x, int *y, int *speed)
{
	mlx_image_t			*ply_collision;
	t_map				*pos;
	int32_t				tcm;

	if (!player->ennemies[1])
		return ;
	ply_collision = player->collision->img;
	tcm = ply_collision->height / 5;
	pos = player->pos->left->upper;
	if (*x == -1 && pos->slot[0] == '1' && ply_collision->instances[0].y + tcm
		< pos->img->instances[0].y + (int32_t)pos->img->height
		&& ply_collision->instances[0].x - *speed
		< pos->img->instances[0].x + (int32_t)pos->img->width)
			*x = 0;
	pos = player->pos->left->below;
	if (*x == -1 && pos->slot[0] == '1' && ply_collision->instances[0].y
		+ (int32_t)ply_collision->height - tcm > pos->img->instances[0].y
		&& ply_collision->instances[0].x - *speed
		< pos->img->instances[0].x + (int32_t)pos->img->width)
			*x = 0;
	pos = player->pos->right->upper;
	if (*x == 1 && pos->slot[0] == '1' && ply_collision->instances[0].y + tcm
		< pos->img->instances[0].y + (int32_t)pos->img->height &&
		ply_collision->instances[0].x + (int32_t)ply_collision->width
		+ *speed >= pos->img->instances[0].x)
			*x = 0;
	pos = player->pos->right->below;
	if (*x == 1 && pos->slot[0] == '1' && ply_collision->instances[0].y
		+ (int32_t)ply_collision->height - tcm > pos->img->instances[0].y
		&& ply_collision->instances[0].x + (int32_t)ply_collision->width
		+ *speed >= pos->img->instances[0].x)
			*x = 0;
	tcm = ply_collision->width / 5;
	pos = player->pos->left->upper;
	if (*y == -1 && pos->slot[0] == '1' && ply_collision->instances[0].x + tcm
		< pos->img->instances[0].x + (int32_t)pos->img->width
		&& ply_collision->instances[0].y - *speed
		< pos->img->instances[0].y + (int32_t)pos->img->height)
			*y = 0;
	pos = player->pos->right->upper;
	if (*y == -1 && pos->slot[0] == '1' && ply_collision->instances[0].x
		+ (int32_t)ply_collision->width - tcm > pos->img->instances[0].x
		&& ply_collision->instances[0].y + (int32_t)ply_collision->height
		- *speed > pos->img->instances[0].y)
			*y = 0;
	pos = player->pos->left->below;
	if (*y == 1 && pos->slot[0] == '1' && ply_collision->instances[0].x + tcm
		< pos->img->instances[0].x + (int32_t)pos->img->width
		&& ply_collision->instances[0].x + *speed
		< pos->img->instances[0].y + (int32_t)pos->img->height)
			*y = 0;
	pos = player->pos->right->below;
	if (*y == 1 && pos->slot[0] == '1' && ply_collision->instances[0].x
		+ (int32_t)ply_collision->width - tcm > pos->img->instances[0].x
		&& ply_collision->instances[0].y + (int32_t)ply_collision->height
		+ *speed <= pos->img->instances[0].y)
			*y = 0;
}

bool	predict_player_pos(t_player	*player, int x, int y, int speed)
{
	mlx_image_t			*ply_collision;

	ply_collision = player->collision->img;
	is_player_in_vertex(player, &x, &y, &speed);
	if (x == 0 && y == 0)
		return (false);
	if (x == -1 && player->pos->left->slot[0] == '1')
	{
		if (ply_collision->instances[0].x - speed
			<= player->pos->left->img->instances[0].x
			+ (int32_t)player->pos->left->img->width)
			return (false);
	}
	if (x == 1 && player->pos->right->slot[0] == '1')
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
	if (y == 1 && player->pos->below->slot[0] == '1')
	{
		if (ply_collision->instances[0].y + (int32_t)ply_collision->height
			+ speed >= player->pos->below->img->instances[0].y)
			return (false);
	}

	actualize_player_map_pos(player, x, y, &speed);
	return (true);
}

int	manage_dash(t_player *player, int speed)
{
	static int	dash_time = PLAYER_DASH_DURATION;

	if (player->can_dash && mlx_is_key_down(player->mlx, MLX_KEY_SPACE))
	{
		dash_time = 0;
		player->can_dash = false;
	}
	if (dash_time >= PLAYER_DASH_DURATION)
		return (speed);
	dash_time++;
	speed = PLAYER_DASH_SPEED * player->mlx->delta_time;
	return (speed);
}

bool	is_game_finish(t_player *player)
{
	int	i;

	i = 0;
	while (player->ennemies[i])
	{
		if (!player->ennemies[i]->on_remove)
			return (false);
		i++;
	}
	if (player->pos->slot[0] != 'E')
		return (false);
	return (true);
}

void	write_movement_count(mlx_t *mlx, int count, int32_t x, int32_t y)
{
	static	mlx_image_t *last_string = NULL;
	static	bool		in_use = false;
	char				*str;

	if (in_use)
		return ;
	in_use = true;
	str = ft_itoa(count);
	if (!str)
		return ;
	if (last_string)
		mlx_delete_image(mlx, last_string);
	last_string = mlx_put_string(mlx, str, x, y);
	free(str);
	in_use = false;
}

void	*move_player(t_player *player, int x, int y, bool *input_pressed)
{
	int		speed;
	t_point	to_add;

	*input_pressed = true;
	set_animation(player, player->walking_sprites, false);
	if (mlx_is_key_down(player->mlx, MLX_KEY_LEFT_SHIFT))
		speed = PLAYER_RUN_SPEED * player->mlx->delta_time;
	else
		speed = PLAYER_WALK_SPEED * player->mlx->delta_time;
	speed = manage_dash(player, speed);
	if (!predict_player_pos(player, x, y, speed))
		return (NULL);
	to_add.x = x * speed;
	to_add.y = y * speed;
	player->collision->img->instances[0].x += to_add.x;
	player->collision->img->instances[0].y += to_add.y;
	player->collision->x_pivot += to_add.x;
	player->collision->y_pivot += to_add.y;
	player->img->instances[0].x += to_add.x;
	player->img->instances[0].y += to_add.y;
	(player->npc_move_count)++;
	if (is_game_finish(player))
		close_mlx(NULL);
	return (NULL);
}

void	player_movement(void *param)
{
	static mlx_t	*mlx = NULL;
	t_player		*player;
	bool			input_pressed;

	input_pressed = false;
	player = (t_player *)param;
	if (!player || player->on_remove)
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
	else
	{
		write_movement_count(player->mlx, player->npc_move_count,
		player->collision->x_pivot, player->collision->y_pivot);
	}
}
