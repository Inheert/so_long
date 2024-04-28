/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:12:01 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/28 07:29:11 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

mlx_image_t	*img_sharing(mlx_image_t *img)
{
	static mlx_image_t	*simg = NULL;

	if (img)
		simg = img;
	return (simg);
}

void	*delete_bullet_trace(void *args)
{
	int32_t		x;
	int32_t		y;
	uint32_t	delay;
	mlx_image_t	*img;


	if (!args)
		return (NULL);
	x = ((t_param *)args)->x;
	y = ((t_param *)args)->y;
	delay = ((t_param *)args)->delay;
	usleep(delay);
	img = img_sharing(NULL);
	mlx_put_pixel(img, x, y, 0x43ff6400);
	free(args);
	return (NULL);
}

void	prepare_delete_bullet_trace(int32_t x, int32_t y, uint32_t delay)
{
	t_param		*param;
	pthread_t	tid;

	param = malloc(sizeof(t_param) * 1);
	if (!param)
		return ;
	param->x = x;
	param->y = y;
	param->delay = delay;
	pthread_create(&tid, NULL, delete_bullet_trace, param);
	pthread_detach(tid);
}

bool is_shoot_hit(t_player *player, t_point current_pos)
{
	t_map *map = player->pos;
	while (map != NULL)
	{
		if (map->x <= current_pos.x && map->x + (int32_t)map->img->width >= current_pos.x
			&& map->y <= current_pos.y && map->y + (int32_t)map->img->height >= current_pos.y)
		{
			if (map->slot[0] == '1')
				return (true);
			break ;
		}
		if (current_pos.x > map->x && current_pos.x > map->img->instances[0].x + (int32_t)map->img->width)
			map = map->right;
		else if (current_pos.x < map->x && current_pos.x < map->img->instances[0].x + (int32_t)map->img->width)
			map = map->left;
		if (current_pos.y > map->y && current_pos.y > map->img->instances[0].y + (int32_t)map->img->height)
			map = map->below;
		else if (current_pos.y < map->y && current_pos.y < map->img->instances[0].y + (int32_t)map->img->height)
			map = map->upper;
	}
	return (false);
}

void	draw_impact(t_point current_pos) {
	mlx_image_t		*img;
	double			angle;
	unsigned int	distance;

	img = img_sharing(NULL);
	if (!img)
		return;
	distance = 0;
	while (distance < BULLET_IMPACT_LINE_SIZE)
	{
		angle = 0;
		while (angle < 2 * M_PI)
		{
			mlx_put_pixel(img, current_pos.x + cos(angle) * distance, current_pos.y + sin(angle) * distance, BULLET_IMPACT_COLOR);
			prepare_delete_bullet_trace(current_pos.x + cos(angle) * distance, current_pos.y + sin(angle) * distance, BULLET_IMPACT_VANISHING_TIME);
			angle += M_PI / BULLET_IMPACT_LINE_PER_SIDE;
			usleep(BULLET_IMPACT_SLOWNESS);
		}
		distance++;
	}
}

void	raycast(t_player *player, t_point start, t_point end, mlx_image_t *img)
{
	t_point	delta;
	t_point	step;
	t_point	current;
	int		error;
	int		error2;

	img = img_sharing(NULL);
	if (!img)
		return ;
	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	if (start.x < end.x)
		step.x = 1;
	else
		step.x = -1;
	if (start.y < end.y)
		step.y = 1;
	else
		step.y = -1;
	current.x = start.x;
	current.y = start.y;
	error = delta.x - delta.y;
	player = (t_player *)player;
	while (current.x > 0 && current.x < MLX_WIN_WIDTH && current.y > 0 && current.y < MLX_WIN_HEIGHT)
	{
		if (is_shoot_hit(player, current))
		{
			draw_impact(current);
			break ;
		}
		error2 = error * 2;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			current.x += step.x;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			current.y += step.y;
		}
		mlx_put_pixel(img, current.x, current.y, BULLET_TRACE_COLOR);
		prepare_delete_bullet_trace(current.x, current.y, BULLET_TRACE_VANISHING_TIME);
		usleep(BULLET_TRACE_SLOWNESS);
	}
}

void	*start_raycast(void *args)
{
	t_player	*player;
	t_point		start;
	t_point		end;
	t_param		*param;

	param = (t_param *)args;
	if (!param)
		return (NULL);
	player = param->player;
	start = param->start;
	end = param->end;
	raycast(player, start, end, NULL);
	free(args);
	return (NULL);
}

void	prepare_raycast_thread(t_player *player, t_point start, t_point end)
{
	t_param		*param;
	pthread_t	tid;

	param = malloc(sizeof(t_param) * 1);
	if (!param)
		return ;
	param->player = player;
	param->start = start;
	param->end = end;
	pthread_create(&tid, NULL, start_raycast, param);
	pthread_detach(tid);
}

void	shoot_bullet(t_player *player)
{
	static mlx_image_t	*bullet_trace_img = NULL;
	t_point				start;
	t_point				end;

	if (!bullet_trace_img)
	{
		bullet_trace_img = mlx_new_image(player->mlx, MLX_WIN_WIDTH, MLX_WIN_HEIGHT);
		mlx_image_to_window(player->mlx, bullet_trace_img, 0, 0);
		img_sharing(bullet_trace_img);
	}
	set_animation(player, player->shoot_sprites, true);
	start.x = player->collision->x_pivot;
	start.y = player->collision->y_pivot;
	end.x = player->x_aiming;
	end.y = player->y_aiming;
	prepare_raycast_thread(player, start, end);
}

void	on_mouse_action(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_player	*player;

	player = (t_player *)param;
	if (!player)
		return ;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		shoot_bullet(player);
	mods = (modifier_key_t)mods;
}

void	player_aiming(double x, double y, void *param)
{
	t_player		*player;

	player = (t_player *)param;
	if (!player)
		return;
	player->x_aiming = x;
	player->y_aiming = y;
}
