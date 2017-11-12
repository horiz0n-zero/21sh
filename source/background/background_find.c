/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 16:03:40 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/17 14:11:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		*background_find(t_dispatch *const dispatch, const pid_t pid,
		int *const index)
{
	size_t	count;
	int		i;

	i = 0;
	count = dispatch->foreground.background.array_count;
	while (count-- > 0)
	{
		if (dispatch->foreground.background.array[i]->pid == pid)
		{
			*index = i;
			return (dispatch->foreground.background.array[i]);
		}
		i++;
	}
	return (NULL);
}
