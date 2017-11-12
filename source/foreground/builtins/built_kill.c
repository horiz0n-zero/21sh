/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_kill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:49:43 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 11:06:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int						built_kill(t_dispatch *const dispatch, char **argv)
{
	pid_t				pid;
	extern char			**environ;
	char				**pargv;
	int					i;

	i = 0;
	pargv = SUPER(dispatch)->foreground.background.percent(dispatch, argv);
	pid = fork();
	if (!pid)
	{
		*pargv = "/bin/kill";
		execve(*pargv, pargv, environ);
		ft_printf(FATAL_EXECVE, *argv, dispatch);
		exit(1);
	}
	else
		waitpid(pid, &dispatch->foreground.status, dispatch->foreground.wait);
	while (pargv[i])
		free(pargv[i++]);
	free(pargv);
	return (dispatch->foreground.status);
}
