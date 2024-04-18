/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:48:19 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/18 15:14:10 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	t_sprites_add_back(t_sprites **sprites, t_sprites *new)
{
	t_sprites	*first;
	t_sprites	*temp;

	if (!new)
		return ;
	if (!*sprites)
	{
		*sprites = new;
		new->next = new;
		return ;
	}
	first = *sprites;
	temp = *sprites;
	while (temp->next != first)
		temp = temp->next;
	temp->next = new;
	new->next = *sprites;
}

t_sprites	*create_sprite(t_player *player, char *path, unsigned int sprite_n)
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
		return (raise_error(MLX_TEXTURE_ERROR), NULL);
	sprite->img = mlx_texture_to_image(player->mlx, texture);
	if (!sprite->img)
		return (raise_error(MLX_IMG_ERROR), NULL);
	if (!mlx_resize_image(sprite->img, MLX_WIN_HEIGHT / PLAYER_SIZE_DIV, MLX_WIN_HEIGHT / PLAYER_SIZE_DIV))
		return (raise_error(MLX_IMG_ERROR), NULL);
	if (mlx_image_to_window(player->mlx, sprite->img, 0, 0) == -1)
		return (mlx_close_window(player->mlx), raise_error(MLX_IMG_ERROR), NULL);
	sprite->img->enabled = false;
	return (sprite);
}

t_sprites	*create_animation_chain(t_player *player, char *sprites_path, unsigned char sprites_count)
{
	t_sprites	*sprites;
	t_sprites	*sprite;
	int			i;

	sprites = NULL;
	i = 0;
	while (i <= sprites_count)
	{
		sprite = create_sprite(player, sprites_path, i);
		if (!sprite)
			return (mlx_close_window(player->mlx), raise_error(SPRITES_CREATION_ERROR), NULL);
		t_sprites_add_back(&sprites, sprite);
		i++;
	}
	return (sprites);
}
