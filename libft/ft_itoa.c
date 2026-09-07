/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:18:50 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/07 18:18:51 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	number_length(long number)
{
	size_t	length;

	length = 1;
	if (number < 0)
	{
		length++;
		number = -number;
	}
	while (number >= 10)
	{
		number /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	number;
	size_t	length;

	number = n;
	length = number_length(number);
	result = malloc(length + 1);
	if (!result)
		return (NULL);
	result[length] = '\0';
	if (number < 0)
	{
		result[0] = '-';
		number = -number;
	}
	if (number == 0)
		result[0] = '0';
	while (number > 0)
	{
		result[--length] = number % 10 + '0';
		number /= 10;
	}
	return (result);
}
