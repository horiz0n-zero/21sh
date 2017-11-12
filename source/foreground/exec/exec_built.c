/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:09:32 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/06 13:09:52 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	builtins_red(t_task *const task, t_cmd *const cmd,
		int *const fd)
{
	if (task->stdin != STDIN_FILENO || cmd->stdin != STDIN_FILENO)
		fd[0] = dup(STDIN_FILENO);
	else
		fd[0] = -1;
	if (task->stdout != STDOUT_FILENO || cmd->stdout != STDOUT_FILENO)
		fd[1] = dup(STDOUT_FILENO);
	else
		fd[1] = -1;
	if (task->stderr != STDERR_FILENO || cmd->stderr != STDERR_FILENO)
		fd[2] = dup(STDERR_FILENO);
	else
		fd[2] = -1;
}

static inline void	builtins_red_close(int *const fd)
{
	if (fd[0] != -1)
	{
		close(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
	}
	if (fd[1] != -1)
	{
		close(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (fd[2] != -1)
	{
		close(STDERR_FILENO);
		dup2(fd[2], STDERR_FILENO);
	}
}

void				exec_built(t_dispatch *const dispatch, t_task *const task,
		t_cmd *const cmd)
{
	int				fd[3];

	builtins_red(task, cmd, fd);
	SUPER(dispatch)->foreground.set_std(task, cmd);
	dispatch->foreground.status = ((builtfunc)cmd->func)(dispatch, cmd->argv);
	builtins_red_close(fd);
}
