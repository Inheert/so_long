/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:25:44 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/01 10:52:06 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>

void	add_slots_to_map(t_map *map, char *line)
{
	map++;
	line++;
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
	return ;
	while (line)
	{
		add_slots_to_map(map, line);
		garbage_collector(DELETE, line);
		line = get_next_line(fd);
	}
	garbage_collector(DELETE, line);
	map++;
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
