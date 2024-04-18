/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aiming.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:45:26 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/18 12:38:16 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	player_aiming(double x, double y, void *param)
{
	static mlx_t	*mlx = NULL;
	t_player		*player;
	double			angle_rad;
	double			angle_deg;

	player = (t_player *)param;
	if (!player)
		return;
	if (!mlx)
		mlx = player->mlx;
	angle_rad = atan2(y - player->collision->y_pivot, x - player->collision->x_pivot);
	angle_deg = angle_rad * (180 / M_PI);
	angle_deg++;
	//printf("Angle:%f\n", angle_deg);
}
