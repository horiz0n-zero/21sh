/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tmp_breakloop.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 11:00:32 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/05 11:18:48 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void					display_tmp_breakloop(t_dispatch *const dispatch)
{
	static int64_t		data;
	static char *const	ptr = (void*)&data;
	ssize_t				size;

	dispatch->display.work = WORKD_TXT;
	while (true)
	{
		size = read(STDIN_FILENO, ptr, sizeof(int64_t));
		if (size == 1)
		{
			if (*(char*)ptr == 3)
				break ;
			if (*(char*)ptr == 13)
			{
				write(STDOUT_FILENO, "\n", 1);
				while (dispatch->display.buffer_size <
						dispatch->display.len + 1)
					SUPER(dispatch)->display.expand(dispatch);
				dispatch->display.buffer[dispatch->display.index++] = '\n';
				dispatch->display.len++;
				continue ;
			}
			SUPER(dispatch)->display.read_one(ptr, dispatch);
		}
		else
			SUPER(dispatch)->display.read_three(ptr, dispatch);
		if (!dispatch->display.work)
			return ;
	}
	dispatch->display.work = WORKD_MAIN;
}
