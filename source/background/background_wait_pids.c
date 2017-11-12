/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_wait_pids.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 11:18:54 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 10:48:29 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		background_wait_pids(t_dispatch *const dispatch)
{
	size_t	index;
	pid_t	pid;

	index = 0;
	signal(SIGCHLD, SIG_DFL);
	while (index < dispatch->foreground.background.pids_count)
	{
		pid = dispatch->foreground.background.pids[index++];
		waitpid(pid, &dispatch->foreground.status, dispatch->foreground.wait);
	}
	signal(SIGCHLD, signal_child);
	dispatch->foreground.background.pids_count = 0;
}
