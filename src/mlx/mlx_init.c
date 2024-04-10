/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:11:07 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/10 09:52:39 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	set_pixel(mlx_image_t *img)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			mlx_put_pixel(img, x, y, 0x00FFCCFF);
			y++;
		}
		x++;
	}
}

void	test_func(t_map *map, mlx_t *mlx)
{
	static mlx_t	*smlx = NULL;
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	if (!smlx && mlx)
		smlx = mlx;
	if (!map || !smlx)
		return ;
	texture = mlx_load_png("./src/maps/textures/download/256Tiles Square02Grass.png");
	if (!texture)
		return (mlx_close_window(smlx), raise_error(MLX_TEXTURE_ERROR));
	img = mlx_texture_to_image(smlx, texture);
	if (!img)
		return (mlx_close_window(smlx), raise_error(MLX_IMG_ERROR));
	if (mlx_image_to_window(smlx, img, 0, 0) == -1)
		return (mlx_close_window(smlx), raise_error(MLX_IMG_ERROR));
	if (!map->left)
		img->instances[0].x = 0;
	else
		img->instances[0].x = map->left->img->instances[0].x + MLX_IMG_WIDTH;
	if (!map->upper)
		img->instances[0].y = 0;
	else
		img->instances[0].y = map->upper->img->instances[0].y + MLX_IMG_WIDTH;
	map->img = img;
}

void	_mlx_create_map(mlx_t *mlx, t_map *map)
{
	test_func(NULL, mlx);
	apply_func_on_map(map, test_func);
	mlx++;
}

void	start_mlx(t_map *map)
{
	mlx_t	*mlx;

	mlx = mlx_init(MLX_WIN_WIDTH, MLX_WIN_HEIGHT, "so_long", true);
	if (!mlx)
		raise_error(MLX_ERROR);
	_mlx_create_map(mlx, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	map++;
}
