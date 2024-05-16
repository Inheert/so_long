/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:53:22 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 13:32:49 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_map_info	*map_info;

	check_args(argc, argv);
	map_info = map_parsing(argv[1]);
	start_mlx(map_info);
	garbage_collector(CLEAR, NULL);
	return (0);
}
