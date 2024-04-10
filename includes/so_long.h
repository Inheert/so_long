/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:39:28 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/10 06:41:57 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "../libft/libft.h"

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
void	raise_error(char *error);
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
