/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_dispatch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 10:37:42 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void __attribute__ ((noreturn))		dtor_dispatch(t_dispatch *const dispatch)
{
	SUPER(dispatch)->env.dtor(dispatch);
	SUPER(dispatch)->display.dtor(dispatch);
	SUPER(dispatch)->foreground.dtor(dispatch);
	SUPER(dispatch)->saver.dtor(dispatch);
	exit(0);
}
