/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:01:55 by tclaereb          #+#    #+#             */
/*   Updated: 2024/05/16 13:35:49 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	*ft_malloc(size_t size, size_t nmemb)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (size == 0 || nmemb == 0)
		raise_error(MALLOC_ERROR, NULL);
	else if (nmemb > (size_t)-1 / size)
		raise_error(MALLOC_OVEFLOW, NULL);
	ptr = malloc(size * (nmemb + 1));
	if (!ptr)
		raise_error(MALLOC_ERROR, NULL);
	while (i < size * nmemb)
		((char *)ptr)[i++] = 0;
	garbage_collector(ADD, ptr);
	return (ptr);
}
