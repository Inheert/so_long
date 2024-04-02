/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:39:28 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/02 08:05:19 by tclaereb         ###   ########.fr       */
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
} t_error;

typedef enum {
	ADD,
	DELETE,
	CLEAR,
} t_garbage_action;

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_map
{
	char			slot;
	struct s_map	*left;
	struct s_map	*right;
	struct s_map	*upper;
	struct s_map	*below;
} t_map;

//#define malloc(size) ft_malloc(size, 1)

void	*ft_malloc(size_t size, size_t nmemb);
void	ft_error(t_error error);
void	garbage_collector(t_garbage_action action, void *ptr);
void	check_args(int argc, char **argv);
char	*ft_strjoin_enhanced(char *s1, char *s2);
char	*get_full_path(char *filename);
t_map	*map_parsing(char *filename);

#endif
