/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:53:22 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/02 08:22:47 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	//garbage_collector(ADD, malloc(2));
	map_parsing(argv[1]);
	garbage_collector(CLEAR, NULL);
	return (0);
}
