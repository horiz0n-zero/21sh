/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 11:13:42 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 10:00:11 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void				insert_globing(t_dispatch *const dispatch)
{
	char				**ptr;

	ptr = malloc(sizeof(void*) * 3);
	*ptr = string_copy("un");
	*(ptr + 1) = string_copy("teste");
	*(ptr + 2) = NULL;
	karray(dispatch->foreground.split, dispatch->foreground.index, true);
	arrayinsert(dispatch, ptr);
}

void					foreground_insert(t_dispatch *const dispatch,
		const int type)
{
	if (type & 16)
		insert_globing(dispatch);
	else
		SUPER(dispatch)->foreground.get_inibit(dispatch, NULL);
}
