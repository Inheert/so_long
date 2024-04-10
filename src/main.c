/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:53:22 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/10 06:35:53 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	check_args(argc, argv);
	map = map_parsing(argv[1]);
	map++;
	garbage_collector(CLEAR, NULL);
	return (0);
}
