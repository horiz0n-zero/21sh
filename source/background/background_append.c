/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 13:13:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/17 14:11:24 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			background_expand(t_dispatch *const dispatch)
{
	void **const	array = (void*)dispatch->foreground.background.array;
	size_t			size;
	int				index;

	index = 0;
	size = dispatch->foreground.background.array_size;
	dispatch->foreground.background.array_size *= 2;
	if (!(dispatch->foreground.background.array = malloc(sizeof(void*) *
					(dispatch->foreground.background.array_size + 1))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset((void*)dispatch->foreground.background.array, (sizeof(void*) *
				(dispatch->foreground.background.array_size + 1)));
	while (size-- > 0)
	{
		dispatch->foreground.background.array[index] = array[index];
		index++;
	}
	free(array);
}

void				background_append(t_dispatch *const dispatch,
		void *const element)
{
	size_t			norme;

	if (dispatch->foreground.background.array_count + 1 >
			dispatch->foreground.background.array_size)
		background_expand(dispatch);
	norme = dispatch->foreground.background.array_count++;
	dispatch->foreground.background.array[norme] = element;
}
