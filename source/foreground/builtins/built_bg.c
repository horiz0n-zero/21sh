/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:34:24 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 11:20:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			bg_send_continue(t_dispatch *const dispatch, const char *src)
{
	const pid_t		pid = SUPER(dispatch)->string.atoi(src);

	kill(pid, SIGCONT);
}

static void			bg_continue(t_dispatch *const dispatch)
{
	void **const	array = (void*)dispatch->foreground.background.array;
	t_bg *const		bg = array[dispatch->foreground.background.array_count - 1];

	kill(SIGCONT, bg->pid);
}

int					built_bg(t_dispatch *const dispatch, char **argv)
{
	char			**pargv;
	int				i;

	pargv = SUPER(dispatch)->foreground.background.percent(dispatch, argv);
	i = 0;
	if (*(pargv + 1))
	{
		while (*pargv)
			bg_send_continue(dispatch, *pargv++);
	}
	else
	{
		if (dispatch->foreground.background.array_count)
			bg_continue(dispatch);
		else
			ft_printf("%s : no current job\n", *pargv);
	}
	while (pargv[i])
		free(pargv[i++]);
	free(pargv);
	return (0);
}
