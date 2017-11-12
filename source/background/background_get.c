/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 13:17:34 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/11 13:37:44 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		*background_get(t_dispatch *const dispatch, const int index)
{
	if ((size_t)index > dispatch->foreground.background.array_count)
		return (NULL);
	else
		return (dispatch->foreground.background.array[index]);
}
