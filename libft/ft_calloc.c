/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:18:38 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/07 18:18:39 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*memory;
	size_t			total;
	size_t			i;

	if (size != 0 && count > ((size_t)-1) / size)
		return (NULL);
	total = count * size;
	memory = malloc(total);
	if (!memory)
		return (NULL);
	i = 0;
	while (i < total)
		memory[i++] = 0;
	return (memory);
}
