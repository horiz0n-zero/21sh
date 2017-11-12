/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 11:54:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/09 14:43:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			dtor_background(t_dispatch *const dispatch)
{
	void		**array;
	t_bg		*bg;
	char		**argv;

	array = (void*)dispatch->foreground.background.array;
	while (dispatch->foreground.background.array_count-- > 0)
	{
		bg = *dispatch->foreground.background.array++;
		argv = bg->argv;
		kill(bg->pid, SIGKILL);
		ft_printf("\33[38;5;160m>> kill %s\n", *bg->argv);
		while (*argv)
			free(*argv++);
		free(bg->argv);
		free(bg);
	}
	free(array);
	free(dispatch->foreground.background.pids);
}
