/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:39:28 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/16 17:05:05 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define MALLOC_ERROR "Malloc error.\n\0"
# define MALLOC_OVEFLOW "Malloc overflow.\n\0"
# define NO_VALID_ARGS_COUNT "Args count is no equal to 2.\n\0"
# define NO_VALID_ARG "Arg don't have .ber extension or dont have a valid path.\n\0"
# define NO_VALID_MAP "Map is not valid.\n\0"
# define NO_VALID_MAP_LINE_LEN "Map line len is not equal to the first line len.\n\0"
# define UNKNOW_MAP_SYMBOL "Unknow map symbol.\n\0"
# define MISSING_SYMBOL "There is missing symbols (start, exit or collectible).\n\0"
# define NO_VALID_PATH "Map have no valid path.\n\0"
# define MLX_ERROR "A problem has occured when using MLX.\n\0"
# define MLX_IMG_ERROR "A problem has occured when using MLX image.\n\0"
# define MLX_TEXTURE_ERROR "A problem has occured when using MLX texture.\n\0"
# define PLAYER_CREATION_ERROR "A problem has occured when creating player.\n\0"


# define MLX_WIN_WIDTH 3860
# define MLX_WIN_HEIGHT 2100
# define MLX_IMG_WIDTH 150

typedef enum {
	ADD,
	DELETE,
	CLEAR,
} t_garbage_action;

typedef enum {
	LEFT,
	RIGHT,
	UPPER,
	BELOW,
} t_direction;

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_check_symbols
{
	int		is_exit_exist;
	int		is_start_exist;
	int		is_collectible_exist;
} t_check_symbols;

typedef struct s_map
{
	char			slot[2];
	struct s_map	*left;
	struct s_map	*right;
	struct s_map	*upper;
	struct s_map	*below;
	mlx_image_t		*img;
	int				x;
	int				y;
} t_map;

typedef struct s_map_info
{
	t_map	*map;
	int		map_width;
	int		map_height;
} t_map_info;

typedef struct s_player
{
	t_map		*pos;
	mlx_image_t	*img;
} t_player;

//#define malloc(size) ft_malloc(size, 1)

ssize_t 	str_ptr_len(char **str);
void		*ft_malloc(size_t size, size_t nmemb);
void		raise_error(char *error);
void		garbage_collector(t_garbage_action action, void *ptr);
void		check_args(int argc, char **argv);
char		*ft_strjoin_enhanced(char *s1, char *s2);
char		*get_full_path(char *filename);
int			is_valid_symbol(char symbol[2]);
int			is_wall_valid(t_map *map);
int			is_char_missing(t_map *map, t_map *tmp);
int			is_valid_path_exist(t_map *map);

t_map_info	*map_parsing(char *filename);
t_map		*map_new(char slot[2]);
t_map		*copy_map(t_map *map);
t_map		*get_start_pos(t_map *map);

int 		*get_map_len(t_map *map);

void		map_add_right(t_map **map, t_map *new);
void		map_add_below(t_map **map, t_map *new);
void		map_link_lines(t_map *first_line, t_map *second_line);
void		apply_func_on_map(t_map *map, void (*f)(t_map *map, mlx_t *mlx, int width, int height));
void		display_map(t_map *map, int display_link);

void		start_mlx(t_map_info *map_info);
void		close_mlx(mlx_t *mlx);
void		init_mlx_hooks(mlx_t *mlx);
void		ft_key_hook(mlx_key_data_t keydata, void* param);

void		init_player(t_map *map);
t_map		*find_player_pos(t_map *map);

#endif
