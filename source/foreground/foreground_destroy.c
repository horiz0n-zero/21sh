/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 10:36:51 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/06 13:47:00 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	destroy_task(t_task *const task)
{
	if (task->stdin != STDIN_FILENO)
		close(task->stdin);
	if (task->stdout != STDOUT_FILENO)
		close(task->stdout);
	if (task->stderr != STDERR_FILENO)
		close(task->stderr);
}

static inline void	destroy_cmd(t_cmd *const cmd)
{
	if (cmd->stdin != STDIN_FILENO)
		close(cmd->stdin);
	if (cmd->stdout != STDOUT_FILENO)
		close(cmd->stdout);
	if (cmd->stderr != STDERR_FILENO)
		close(cmd->stderr);
	if (cmd->argv && cmd->isdone)
		free(cmd->argv);
}

static inline void	foreground_free(t_dispatch *const dispatch)
{
	char			**split;

	dispatch->foreground.index = 0;
	dispatch->foreground.need_task = false;
	dispatch->foreground.collection.task = NULL;
	dispatch->foreground.collection.ctask = NULL;
	dispatch->foreground.collection.ccmd = NULL;
	split = dispatch->foreground.split;
	while (*split)
		free(*split++);
	free(dispatch->foreground.split);
	dispatch->foreground.split = NULL;
}

void				foreground_destroy(t_dispatch *const dispatch)
{
	t_task			*task;
	t_cmd			*cmd;
	void			*tmp;

	task = dispatch->foreground.collection.task;
	while (task)
	{
		cmd = task->cmd;
		while (cmd)
		{
			tmp = cmd;
			destroy_cmd(cmd);
			cmd = cmd->next;
			free(tmp);
		}
		tmp = task;
		destroy_task(task);
		task = task->next;
		free(tmp);
	}
	foreground_free(dispatch);
}
