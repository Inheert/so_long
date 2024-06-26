/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:48:19 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 13:40:32 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	t_sprites_add_back(t_sprites **sprites, t_sprites *new, bool is_loop)
{
	t_sprites	*first;
	t_sprites	*temp;

	if (!new)
		return ;
	if (!*sprites)
	{
		*sprites = new;
		new->next = new;
		new->prev = NULL;
		return ;
	}
	first = *sprites;
	temp = *sprites;
	while (temp->next && temp->next != first)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	if (is_loop)
	{
		new->next = *sprites;
		*sprites = new;
	}
}

t_sprites	*create_sprite(t_player *player, t_map_info *map, char *path,
	unsigned int sprite_n)
{
	char			*fullpath;
	char			*sprite_idx;
	t_sprites		*sprite;
	mlx_texture_t	*texture;

	sprite_idx = ft_itoa(sprite_n);
	sprite_n = ft_strlen(path) + ft_strlen(sprite_idx) + 5;
	fullpath = ft_malloc(sizeof(char), sprite_n);
	ft_strlcat(fullpath, path, sprite_n);
	ft_strlcat(fullpath, sprite_idx, sprite_n);
	ft_strlcat(fullpath, ".png", sprite_n);
	sprite = ft_malloc(sizeof(t_sprites), 1);
	texture = mlx_load_png(fullpath);
	if (!texture)
		return (raise_error(MLX_TEXTURE_ERROR, NULL), NULL);
	garbage_collector(ADD_TEXTURE, texture);
	sprite->img = mlx_texture_to_image(player->mlx, texture);
	if (!sprite->img || !mlx_resize_image(sprite->img, MLX_WIN_WIDTH
			/ map->map_width, MLX_WIN_WIDTH / map->map_height))
		return (raise_error(MLX_IMG_ERROR, NULL), NULL);
	if (mlx_image_to_window(player->mlx, sprite->img, 0, 0) == -1)
		return (mlx_close_window(player->mlx),
			raise_error(MLX_IMG_ERROR, NULL), NULL);
	garbage_collector(ADD_IMG, sprite->img);
	sprite->img->enabled = false;
	return (free(sprite_idx), sprite);
}

t_sprites	*create_animation_chain(t_player *player, t_map_info *map, bool is_loop,
	char *sprites_path)
{
	t_sprites		*sprites;
	t_sprites		*sprite;
	t_sprite_types	type;
	unsigned char	sprites_count;
	int				i;
	if (ft_strncmp(sprites_path, S_HANDGUN_IDLE_PATH, ft_strlen(sprites_path)) == 0)
	{
		type = IDLE;
		sprites_count = S_HANDGUN_IDLE_COUNT;
	}
	else if (ft_strncmp(sprites_path, S_HANDGUN_WALK_PATH, ft_strlen(sprites_path)) == 0)
	{
		type = WALK;
		sprites_count = S_HANDGUN_WALK_COUNT;
	}
	else if (ft_strncmp(sprites_path, S_HANDGUN_SHOOT_PATH, ft_strlen(sprites_path)) == 0)
	{
		type = SHOOT;
		sprites_count = S_HANDGUN_SHOOT_COUNT;
	}
	else if (ft_strncmp(sprites_path, S_HANDGUN_MELEE_PATH, ft_strlen(sprites_path)) == 0)
	{
		type = MELEE;
		sprites_count = S_HANDGUN_MELEE_COUNT;
	}
	else
		return (raise_error(SPRITES_CREATION_ERROR, NULL), NULL);

	sprites = NULL;
	i = 0;
	while (i <= sprites_count)
	{
		sprite = create_sprite(player, map, sprites_path, i);
		if (!sprite)
			return (mlx_close_window(player->mlx),
				raise_error(SPRITES_CREATION_ERROR, NULL), NULL);
		sprite->type = type;
		t_sprites_add_back(&sprites, sprite, is_loop);
		i++;
	}
	return (sprites);
}
