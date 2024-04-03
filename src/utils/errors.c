/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:13:33 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/03 11:04:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

const char	*get_error_string(t_error error)
{
	const char	*error_strings[7] = {
		"Malloc error.\0",
		"Malloc overflow.\0",
		"Args count is no equal to 2.\0",
		"Arg don't have .ber extension or dont have a valid path.\0",
		"Map is not valid.\0",
		"Map line len is not equal to the first line len.\0",
		"Unknow map symbol.\0"
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
