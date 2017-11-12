/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_set_std.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:03:50 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/07 10:03:51 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		foreground_set_std(t_task *const task, t_cmd *const cmd)
{
	if (task->stdin != STDIN_FILENO && cmd->stdin == STDIN_FILENO)
		cmd->stdin = task->stdin;
	if (task->stdout != STDOUT_FILENO && cmd->stdout == STDOUT_FILENO)
		cmd->stdout = task->stdout;
	if (task->stderr != STDERR_FILENO && cmd->stderr == STDERR_FILENO)
		cmd->stderr = task->stderr;
	if (cmd->stdin != STDIN_FILENO)
	{
		close(STDIN_FILENO);
		dup2(cmd->stdin, STDIN_FILENO);
	}
	if (cmd->stdout != STDOUT_FILENO)
	{
		close(STDOUT_FILENO);
		dup2(cmd->stdout, STDOUT_FILENO);
	}
	if (cmd->stderr != STDERR_FILENO)
	{
		close(STDERR_FILENO);
		dup2(cmd->stderr, STDERR_FILENO);
	}
}
