/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:11:07 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/09 08:46:02 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

mlx_image_t	*create_img(t_map *map, mlx_t *mlx, int width, int height)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	if (!map || !mlx)
		return (NULL);
	if (map->slot[0] == '1')
		texture = mlx_load_png(
				"./src/textures/decor/256Tiles Square02Grass.png");
	else
		texture = mlx_load_png("./src/textures/decor/256_Dirt Pebbles 01.png");
	if (!texture)
		return (mlx_close_window(mlx), raise_error(MLX_TEXTURE_ERROR), NULL);
	garbage_collector(ADD_TEXTURE, texture);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	if (!mlx_resize_image(img, MLX_WIN_WIDTH / width, MLX_WIN_HEIGHT / height))
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	garbage_collector(ADD_IMG, img);
	return (img);
}

mlx_image_t	*create_overlay(t_map *map, mlx_t *mlx, int width, int height)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	if (!map || !mlx)
		return (NULL);
	if (map->slot[0] == 'E')
		texture = mlx_load_png(
				"./src/textures/decor/256_Mound 05.png");
	else
		return (NULL);
	if (!texture)
		return (mlx_close_window(mlx), raise_error(MLX_TEXTURE_ERROR), NULL);
	garbage_collector(ADD_TEXTURE, texture);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	if (!mlx_resize_image(img, MLX_WIN_WIDTH / width, MLX_WIN_WIDTH / height))
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		return (mlx_close_window(mlx), raise_error(MLX_IMG_ERROR), NULL);
	garbage_collector(ADD_IMG, img);
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
	if (!img)
		return ;
	if (!map->left)
		img->instances[0].x = 0;
	else
		img->instances[0].x = map->left->img->instances[0].x
			+ MLX_WIN_WIDTH / map_width;
	if (!map->upper)
		img->instances[0].y = 0;
	else
		img->instances[0].y = map->upper->img->instances[0].y
			+ MLX_WIN_HEIGHT / map_height;
	map->img = img;
	map->x = img->instances[0].x;
	map->y = img->instances[0].y;
}

void	set_overlay(t_map *map, mlx_t *mlx, int width, int height)
{
	static mlx_t	*smlx = NULL;
	static int		map_width = 0;
	static int		map_height = 0;

	if (!smlx && mlx)
		smlx = mlx;
	if (!map_width || !map_height)
	{
		map_width = width;
		map_height = height;
	}
	if (!map || !smlx || !map_width || !map_height)
		return ;
	map->overlay = create_overlay(map, smlx, map_width, map_height);
	if (map->overlay)
	{
		map->overlay->instances[0].x = map->x;
		map->overlay->instances[0].y = map->y;
	}
}

void	mlx_create_map(mlx_t *mlx, t_map_info *map_info)
{
	set_img(NULL, mlx, map_info->map_width, map_info->map_height);
	set_overlay(NULL, mlx, map_info->map_width, map_info->map_height);
	apply_func_on_map(map_info->map, set_img);
	apply_func_on_map(map_info->map, set_overlay);
	mlx++;
}

mlx_win_cursor_t	*create_mlx_cursor(void)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./src/textures/player/cursor/crosshair1.png");
	if (!texture)
		return (raise_error(MLX_TEXTURE_ERROR), close_mlx(NULL), NULL);
	garbage_collector(ADD_TEXTURE, texture);
	return (mlx_create_cursor(texture));
}

void	start_mlx(t_map_info *map_info)
{
	mlx_t		*mlx;

	mlx = mlx_init(MLX_WIN_WIDTH, MLX_WIN_HEIGHT, "so_long", true);
	if (!mlx)
		raise_error(MLX_ERROR);
	garbage_collector(INIT, mlx);
	close_mlx(mlx);
	mlx_create_map(mlx, map_info);
	init_all_npcs(mlx, map_info, init_player(mlx, map_info));
	mlx_set_cursor(mlx, create_mlx_cursor());
	init_mlx_hooks(mlx, map_info);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

void	close_mlx(mlx_t *mlx)
{
	static mlx_t	*smlx = NULL;

	if (!smlx && mlx)
	{
		smlx = mlx;
		return ;
	}
	if (!smlx)
		return ;
	mlx_close_window(smlx);
	garbage_collector(CLEAR, NULL);
	exit(0);
}
