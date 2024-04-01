/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:13:33 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/01 10:49:38 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

const char	*error_strings[5] = {
	"Malloc error.",
	"Malloc overflow.",
	"Args count is no equal to 2.",
	"Arg don't have .ber extension or dont have a valid path.",
	"Map is not valid.",
};

const char	*get_error_string(t_error error)
{
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
