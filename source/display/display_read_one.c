/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_read_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:54 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 12:27:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			display_read_one(const char *ptr, t_dispatch *const dispatch)
{
	if (*ptr == 127)
		SUPER(dispatch)->display.remove(dispatch);
	else if (*ptr >= '!' || *ptr == 32)
		SUPER(dispatch)->display.append(*ptr, dispatch);
	else
	{
		if (*ptr == 13)
		{
			SUPER(dispatch)->display.end(dispatch);
			if (!dispatch->display.work)
				SUPER(dispatch)->start(dispatch);
			else
			{
				SUPER(dispatch)->display.append('\n', dispatch);
				dispatch->display.work = WORKD_MAIN;
			}
		}
		else if (*ptr == '\f')
			SUPER(dispatch)->display.lclear(dispatch);
		else if (*ptr == 9)
			SUPER(dispatch)->display.selection(dispatch);
		else if (*ptr == 3)
			SUPER(dispatch)->display.cancel(dispatch);
		else if (*ptr == 28 || *ptr == 4)
			SUPER(dispatch)->dtor(dispatch);
//		else if (*ptr == 27)									// esc /!\ OU    MAJ + [left|right|up|down|home|end|pgup|pgdown|delete] OU MAJ + fn{1..19}
//			SUPER(dispatch)->dtor(dispatch);
		else if (*ptr == 1)
			SUPER(dispatch)->display.home(dispatch);
		else if (*ptr == 5)
			SUPER(dispatch)->display.end(dispatch);
		else if (*ptr == 11)
			SUPER(dispatch)->display.cut(dispatch);
		else if (*ptr == 16)
			SUPER(dispatch)->display.paste(dispatch);
	}
}
