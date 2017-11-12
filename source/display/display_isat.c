/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_isat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 11:25:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/20 14:20:56 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int	__attribute__ ((pure))	display_isredge(const size_t n, const size_t of)
{
	if ((n + 1) % of == 0)
		return (1);
	return (0);
}

int	__attribute__ ((pure))	display_isledge(const size_t n, const size_t of)
{
	if ((n + 1) % of == 1)
		return (1);
	return (0);
}
