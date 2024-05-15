/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:29:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/15 19:38:25 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	init_mlx_hooks(mlx_t *mlx, t_map_info *map_info)
{
	mlx_key_hook(mlx, &ft_key_hook, map_info);
	mlx_close_hook(mlx, &close_mlx, NULL);
}
