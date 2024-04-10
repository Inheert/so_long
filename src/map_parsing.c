/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:25:44 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/10 06:42:24 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>

void	add_slots_to_map(t_map **map, char *line)
{
	static ssize_t	line_len = -1;
	static t_map	*last_line = NULL;
	t_map			*new_line;
	char			**splited_line;

	new_line = NULL;
	splited_line = ft_split(line, ' ');
	if (!splited_line)
		raise_error(MALLOC_ERROR);
	if (line_len == -1)
		line_len = str_ptr_len(splited_line);
	else if (line_len != str_ptr_len(splited_line))
		raise_error(NO_VALID_MAP_LINE_LEN);
	while (*splited_line)
	{
		map_add_right(&new_line, map_new(*splited_line));
		splited_line++;
	}
	if (last_line)
		map_link_lines(last_line, new_line);
	else
		*map = new_line;
	last_line = new_line;
}

void	read_map(char *filepath, t_map **map)
{
	char	*line;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		raise_error(NO_VALID_ARG);
	line = get_next_line(fd);
	if (!line)
		raise_error(NO_VALID_MAP);
	while (line)
	{
		garbage_collector(ADD, line);
		add_slots_to_map(map, line);
		garbage_collector(DELETE, line);
		line = get_next_line(fd);
	}
}

void	check_map_validity(t_map *map)
{
	t_map	*tmp;

	tmp = NULL;
	if (!is_wall_valid(map))
		raise_error(NO_VALID_MAP);
	else if (is_char_missing(map, tmp))
		raise_error(MISSING_SYMBOL);
	tmp = copy_map(map);
	if (!is_valid_path_exist(tmp))
		raise_error(NO_VALID_PATH);
}

t_map	*map_parsing(char *filename)
{
	char	*filepath;
	t_map	*map;

	map = NULL;
	filepath = get_full_path(filename);
	read_map(filepath, &map);
	check_map_validity(map);
	return (map);
}
