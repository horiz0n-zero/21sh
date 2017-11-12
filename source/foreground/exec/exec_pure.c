/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:19:53 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/11 10:48:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				exec_pure(t_dispatch *const dispatch, t_task *const task,
		t_cmd *const cmd)
{
	extern char		**environ;
	pid_t			pid;

	if (!(pid = fork()))
	{
		if (!(cmd->typeoff == TYPE_AND))
			setpgid(pid, dispatch->foreground.background.self_group);
		else
			setpgid(pid, pid);
		SUPER(dispatch)->foreground.set_std(task, cmd);
		SUPER(dispatch)->foreground.setsignal(DEFAULT);
		execve(*cmd->argv, cmd->argv, environ);
		ft_printf(FATAL_EXECVE, cmd->argv ? *cmd->argv : "BAD", cmd);
		exit(1);
	}
	else if (pid == -1)
		ft_printf(FATAL_FORK, *cmd->argv);
	else
	{
		if (cmd->typeoff == TYPE_AND && !cmd->type)
			*dispatch->foreground.background.pointee_pid = pid;
		cmd->pid = pid;
		dispatch->foreground.background.execute = pid;
		signal(SIGCHLD, SIG_DFL);
		waitpid(pid, &dispatch->foreground.status, dispatch->foreground.wait);
		signal(SIGCHLD, signal_child);
	}
}
