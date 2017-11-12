/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:38:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/10 11:27:25 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

char			*string_itoa(int number)
{
	char		*new;
	size_t		index;
	int			n;

	index = 0;
	n = number;
	while (n)
	{
		index++;
		n /= 10;
	}
	if (!(new = malloc(index + 1)))
		malloc_exit();
	new[index] = 0;
	while (number)
	{
		new[--index] = number % 10 + '0';
		number /= 10;
	}
	return (new);
}
