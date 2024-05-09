/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:20:14 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/08 03:42:59 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_map_info	*map_info;
	map_info = (t_map_info *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		if (map_info && map_info->map)
			map_info->map->on_remove = true;
		usleep(1000000);
		close_mlx(NULL);
	}
}
