/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:01:55 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/10 06:38:38 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	*ft_malloc(size_t size, size_t nmemb)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (size == 0 || nmemb == 0)
		raise_error(MALLOC_ERROR);
	else if (nmemb > (size_t)-1 / size)
		raise_error(MALLOC_OVEFLOW);
	ptr = malloc(size * (nmemb + 1));
	if (!ptr)
		raise_error(MALLOC_ERROR);
	while (i < size * nmemb)
		((char *)ptr)[i++] = 0;
	garbage_collector(ADD, ptr);
	return (ptr);
}
