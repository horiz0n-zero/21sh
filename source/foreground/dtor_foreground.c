/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_foreground.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:36:28 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 10:38:01 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		dtor_foreground(t_dispatch *const dispatch)
{
	SUPER(dispatch)->foreground.binaries.dtor(dispatch);
	SUPER(dispatch)->foreground.setsignal(DEFAULT);
	SUPER(dispatch)->foreground.background.dtor(dispatch);
	SUPER(dispatch)->foreground.collection.dtor(dispatch);
	if (dispatch->foreground.aliaspath)
		SUPER(dispatch)->foreground.alias.dtor(dispatch);
	SUPER(dispatch)->foreground.builtins.dtor(dispatch);
}
