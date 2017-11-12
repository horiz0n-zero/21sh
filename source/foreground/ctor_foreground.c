/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_foreground.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:36:21 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 14:12:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	foreground_alias(t_dispatch *const dispatch)
{
	char			*ptr;
	int				fd;

	ptr = getenv("HOME");
	if (!ptr)
		dispatch->foreground.aliaspath = NULL;
	else
	{
		dispatch->foreground.aliaspath = ft_strcjoin(ptr, ".42sh_alias", '/');
		fd = open(dispatch->foreground.aliaspath, O_CREAT | O_RDWR | O_APPEND,
				dispatch->foreground.red_mode);
		if (fd == -1)
		{
			printf("fd false");
			free(dispatch->foreground.aliaspath);
			return ;
		}
		else
			dispatch->foreground.aliasfile = fd;
		SUPER(dispatch)->foreground.alias.ctor(dispatch);
	}
}

void				ctor_foreground(t_dispatch *const dispatch)
{
	dispatch->foreground.error = NULL;
	dispatch->foreground.error_required_free = 0;
	dispatch->foreground.split = NULL;
	dispatch->foreground.index = 0;
	dispatch->foreground.need_task = false;
	dispatch->foreground.wait = WUNTRACED;
	dispatch->foreground.red_mode = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;
	foreground_alias(dispatch);
	SUPER(dispatch)->foreground.collection.ctor(dispatch);
	SUPER(dispatch)->foreground.setsignal(SELF);
	SUPER(dispatch)->foreground.binaries.ctor(dispatch);
	SUPER(dispatch)->foreground.builtins.ctor(dispatch);
	SUPER(dispatch)->foreground.background.ctor(dispatch);
}
