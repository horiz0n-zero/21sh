/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_keyboard_cut_paste.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:22:33 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/02 14:25:04 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

#include <string.h>

void			display_cut(t_dispatch *const dispatch)
{
	int len;

	if (dispatch->display.pasteboard)
		free(dispatch->display.pasteboard);
	/*
	** IL EST OU FT_STRDUP LA OH HEIN ???
	*/
	dispatch->display.pasteboard = strdup(dispatch->display.buffer +
			dispatch->display.index);
	len = (int)ft_strlen(dispatch->display.pasteboard);
	while (len-- > 0)
		SUPER(dispatch)->display.delete(dispatch);
}

void			display_paste(t_dispatch *const dispatch)
{
	int i;

	if (dispatch->display.pasteboard)
	{
		i = -1;
		while (dispatch->display.pasteboard[++i])
			SUPER(dispatch)->display.append(dispatch->display.pasteboard[i],
					dispatch);
	}
}
