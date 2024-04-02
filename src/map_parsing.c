/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:25:44 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/02 09:31:12 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>

// Split line, get the length of the splitted line, check if all element have a len of 1
// if not raise error except for the last element who must have a len of 2 or 1
// Make a static to store the first element of the last line, make sure that index for the last line
// and for the actual line are the same so upper and below can be set easily and equal line len can be check
// at the same time
// to avoid unnecessary future check we can also make a function to check if the symbol (map slot) is valid.
void	add_slots_to_map(t_map *map, char *line)
{
	char	**splited_line;

	splited_line = ft_split(line, ' ');
	if (!splited_line)
		ft_error(MALLOC_ERROR);
	map++;
	while (*splited_line)
	{
		//ft_printf("%s, ", *splited_line);
		splited_line++;
	}
}

void	read_map(char *filepath, t_map *map)
{
	char	*line;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		ft_error(NO_VALID_ARG);
	line = get_next_line(fd);
	if (!line)
		ft_error(NO_VALID_MAP);
	while (line)
	{
		garbage_collector(ADD, line);
		add_slots_to_map(map, line);
		garbage_collector(DELETE, line);
		line = get_next_line(fd);
	}
}

t_map	*map_parsing(char *filename)
{
	char	*filepath;
	t_map	*map;

	map = NULL;
	filepath = get_full_path(filename);
	read_map(filepath, map);
	return (map);
}
