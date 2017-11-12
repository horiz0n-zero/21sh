/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_dispatch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:02 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/08 11:28:36 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		ctor_dispatch(t_dispatch *const dispatch, const void *const self)
{
	dispatch->debug = open("/dev/ttys004", O_WRONLY);
	ft_fprintf(dispatch->debug, "\n\33[38;5;112mshell start: %d\33[37m\n",
			(int)getpid());
	dispatch->self = self;
	SUPER(dispatch)->env.ctor(dispatch);
	SUPER(dispatch)->display.ctor(dispatch);
	SUPER(dispatch)->foreground.ctor(dispatch);
	SUPER(dispatch)->saver.ctor(dispatch);
}
