/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_read_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:35:15 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/08 14:08:48 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void					display_read_three(const char *ptr,
		t_dispatch *const dispatch)
{
	const char			c = *(ptr + 2);
	static void			*functions[256] =
	{
		['C'] = (void*)display_right,
		['D'] = (void*)display_left,
		['A'] = (void*)display_up,
		['B'] = (void*)display_down,
		['H'] = (void*)display_home,
		['F'] = (void*)display_end
	};

	if (functions[(int)c])
		((void (*)(t_dispatch *const dispatch))functions[(int)c])(dispatch);
}
