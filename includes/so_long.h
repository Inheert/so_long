/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:39:28 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/08 09:39:28 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "../libft/libft.h"

typedef enum {
	MALLOC_ERROR,
	MALLOC_OVEFLOW,
	NO_VALID_ARGS_COUNT,
	NO_VALID_ARG,
	NO_VALID_MAP,
	NO_VALID_MAP_LINE_LEN,
	UNKNOW_MAP_SYMBOL,
	MISSING_SYMBOL,
	NO_VALID_PATH,
} t_error;

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

typedef struct s_map
{
	char			slot[2];
	struct s_map	*left;
	struct s_map	*right;
	struct s_map	*upper;
	struct s_map	*below;
} t_map;

typedef struct s_check_symbols
{
	int		is_exit_exist;
	int		is_start_exist;
	int		is_collectible_exist;
} t_check_symbols;

//#define malloc(size) ft_malloc(size, 1)

ssize_t str_ptr_len(char **str);
void	*ft_malloc(size_t size, size_t nmemb);
void	ft_error(t_error error);
void	garbage_collector(t_garbage_action action, void *ptr);
void	check_args(int argc, char **argv);
char	*ft_strjoin_enhanced(char *s1, char *s2);
char	*get_full_path(char *filename);
int		is_valid_symbol(char symbol[2]);
int		is_wall_valid(t_map *map);
int		is_char_missing(t_map *map, t_map *tmp);
int		is_valid_path_exist(t_map *map);

t_map	*map_parsing(char *filename);
t_map	*map_new(char slot[2]);
t_map	*copy_map(t_map *map);
t_map	*get_start_pos(t_map *map);

void	map_add_right(t_map **map, t_map *new);
void	map_add_below(t_map **map, t_map *new);
void	map_link_lines(t_map *first_line, t_map *second_line);
void	display_map(t_map *map, int display_link);

#endif
