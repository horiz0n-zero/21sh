/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:35:22 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/05 12:48:00 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		dtor_display(t_dispatch *const dispatch)
{
	//write(STDOUT_FILENO, CAPS(TE).s, CAPS(TE).l);
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &dispatch->display.saved) == -1)
		SUPER(dispatch)->exit(dispatch, "can't set the original term struct\n");
}
