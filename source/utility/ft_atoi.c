/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 10:35:34 by afeuerst          #+#    #+#             */
/*   Updated: 2017/09/11 12:02:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int						ft_atoi(const char *src)
{
	int					result;
	const int			sign = *src == '-' ? 1 && ++src : 0;

	result = 0;
	while (*src >= '0' && *src <= '9')
	{
		result = result * 10 + (*src - 48);
		src++;
	}
	if (sign)
		return (result * -1);
	return (result);
}
