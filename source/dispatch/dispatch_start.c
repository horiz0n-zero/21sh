/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:13 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 11:04:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

/*
static void			pr_list(t_dispatch *const dispatch)
{
	t_task			*task;
	t_cmd			*cmd;
	int 			it = 0;
	int 			ic;
	static const char 	*cmd_type[] =
	{
		"common",
		"redirection only",
		"builtins",
		"background"
	};
	static const char 	*ttypeof[] =
	{
		"nope",
		" &  ",
		" && ",
		" |  ",
		" || ",
		" ;  "
	};

	task = dispatch->foreground.collection.task;
	while (task)
	{
		ft_printf("#%d [%d][%d][%d] %d %s\n", it++, task->stdin, task->stdout,
				task->stderr, task->type,
				task->type & TASK_SUBSHELL ? "subshell" : "common");
		ic = 0;
		cmd = task->cmd;
		while (cmd)
		{
			ft_printf("*%d [%d][%d][%d] [%4s] of type %s", ic++, cmd->stdin, 
				cmd->stdout, cmd->stderr, ttypeof[cmd->typeoff], 
					cmd_type[cmd->type]);
			if (cmd->type == CMD_BUILT)
				ft_printf(" Function : %p %s\n", cmd->func, *cmd->argv);
			else
				ft_printf(" Execute : %s\n", cmd->argv ? *cmd->argv : "BAD");
			int i = 1;
			while (cmd->argv[i])
				ft_printf("%s\n", cmd->argv[i++]);
			cmd = cmd->next;
		}
		task = task->next;
	}
}
*/

static inline void	dispatch_display_routine(t_dispatch *const dispatch)
{
	SUPER(dispatch)->saver.save(dispatch);
	dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.index = 0;
	dispatch->display.indes = 0;
	dispatch->display.len = 0;
	SUPER(dispatch)->display.prompt(NULL, 0, dispatch);
}

void				dispatch_start(t_dispatch *const dispatch)
{
	write(STDOUT_FILENO, "\n", 1);
	if (dispatch->display.len)
	{
		SUPER(dispatch)->foreground.get(dispatch);
		if (dispatch->foreground.error)
		{
			write(STDERR_FILENO, dispatch->foreground.error,
			ft_strlen(dispatch->foreground.error));
			if (dispatch->foreground.error_required_free)
			{
				free(dispatch->foreground.error);
				dispatch->foreground.error_required_free = 0;
			}
			dispatch->foreground.error = NULL;
			SUPER(dispatch)->foreground.destroy(dispatch);
		}
		else
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &dispatch->display.saved);
			SUPER(dispatch)->foreground.execute(dispatch);
			SUPER(dispatch)->foreground.destroy(dispatch);
			tcsetattr(STDIN_FILENO, TCSADRAIN, &dispatch->display.current);
			if (dispatch->foreground.background.turn)
			{
				SUPER(dispatch)->sleep(0, 250000000); // 1 s === 1 000 000 000ns
				dispatch->foreground.background.turn = 0;
			}
		}
	}
	dispatch_display_routine(dispatch);
}
