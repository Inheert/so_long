/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:13:33 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/08 09:39:16 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

const char	*get_error_string(t_error error)
{
	const char	*error_strings[9] = {
		"Malloc error.\n\0",
		"Malloc overflow.\n\0",
		"Args count is no equal to 2.\n\0",
		"Arg don't have .ber extension or dont have a valid path.\n\0",
		"Map is not valid.\n\0",
		"Map line len is not equal to the first line len.\n\0",
		"Unknow map symbol.\n\0",
		"There is missing symbols (start, exit or collectible).\n\0",
		"Map have no valid path.\n\0"
	};
	const char	*error_string;

	error_string = error_strings[error];
	if (!error_string)
		return ("Unknown error.");
	return (error_string);
}

void	ft_error(t_error error)
{
	garbage_collector(CLEAR, NULL);
	ft_printf("Error: %s\n", get_error_string(error));
	exit(1);
}
