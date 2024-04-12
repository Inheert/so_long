/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:11:07 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/12 16:29:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"


mlx_image_t	*create_img(t_map *map, mlx_t *mlx, int width, int height)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	ft_printf("%d %d\n", width, height);
	if (map->slot[0] == '1')
		texture = mlx_load_png("./src/maps/textures/decor/256Tiles Square02Grass.png");
	else
		texture = mlx_load_png("./src/maps/textures/decor/256_Dirt Pebbles 01.png");
	if (!texture)
		return (mlx_close_window(mlx), raise_error(MLX_TEXTURE_ERROR), NULL);
	img = mlx_texture_to_image(mlx, texture);
	mlx_resize_image(img, MLX_WIN_WIDTH / width, MLX_WIN_HEIGHT / height);
	if (!img)
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	return (img);
}

void	set_img(t_map *map, mlx_t *mlx, int width, int height)
{
	static mlx_t	*smlx = NULL;
	static int		map_width = 0;
	static int		map_height = 0;
	mlx_image_t		*img;

	if (!smlx && mlx)
		smlx = mlx;
	if (!map_width || !map_height)
	{
		map_width = width;
		map_height = height;
	}
	if (!map || !smlx || !map_width || !map_height)
		return ;
	img = create_img(map, smlx, map_width, map_height);
	if (!map->left)
		img->instances[0].x = 0;
	else
		img->instances[0].x = map->left->img->instances[0].x + MLX_WIN_WIDTH / map_width;
	if (!map->upper)
		img->instances[0].y = 0;
	else
		img->instances[0].y = map->upper->img->instances[0].y + MLX_WIN_HEIGHT / map_height;
	map->img = img;
}

void	_mlx_create_map(mlx_t *mlx, t_map_info *map_info)
{
	set_img(NULL, mlx, map_info->map_width, map_info->map_height);
	apply_func_on_map(map_info->map, set_img);
	mlx++;
}

void	start_mlx(t_map_info *map_info)
{
	mlx_t	*mlx;

	mlx = mlx_init(MLX_WIN_WIDTH, MLX_WIN_HEIGHT, "so_long", true);
	if (!mlx)
		raise_error(MLX_ERROR);
	_mlx_create_map(mlx, map_info);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
