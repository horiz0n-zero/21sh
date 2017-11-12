/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:22:06 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/06 13:23:14 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void			display_ask(t_dispatch *const dispatch,
		t_cmd *const cmd)
{
	dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1);
	if (!dispatch->display.buffer)
		malloc_exit();
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.index = 0;
	dispatch->display.indes = 0;
	dispatch->display.len = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &dispatch->display.current);
	SUPER(dispatch)->display.tmp_breakloop(dispatch);
	tcsetattr(STDIN_FILENO, TCSANOW, &dispatch->display.saved);
	write(cmd->stdout, dispatch->display.buffer, dispatch->display.len);
}

static void					red_redirect(t_dispatch *const dispatch,
		t_cmd *const cmd)
{
	size_t					buffer_size;
	size_t					len;
	char					*tmp;
	char *const				src = dispatch->display.buffer;

	buffer_size = dispatch->display.buffer_size;
	len = dispatch->display.len;
	display_ask(dispatch, cmd);
	tmp = dispatch->display.buffer;
	dispatch->display.buffer = src;
	dispatch->display.buffer_size ^= buffer_size;
	buffer_size ^= dispatch->display.buffer_size;
	dispatch->display.buffer_size = buffer_size;
	dispatch->display.len ^= len;
	len ^= dispatch->display.len;
	dispatch->display.len ^= len;
	while (len + dispatch->display.len >= dispatch->display.buffer_size)
		SUPER(dispatch)->display.expand(dispatch);
	ft_memmove(dispatch->display.buffer + dispatch->display.len, tmp, len);
	dispatch->display.len += len;
	free(tmp);
}

void						exec_red(t_dispatch *const dispatch,
		t_task *const task, t_cmd *const cmd)
{
	long					buffer;
	ssize_t					size;

	(void)task;
	if (cmd->stdin != STDIN_FILENO && cmd->stdout == STDOUT_FILENO)
	{
		while ((size = read(cmd->stdin, &buffer, sizeof(long))))
			write(STDOUT_FILENO, &buffer, (size_t)size);
	}
	else if (cmd->stdout != STDOUT_FILENO && cmd->stdin == STDIN_FILENO)
	{
		red_redirect(dispatch, cmd);
	}
	else if (cmd->stdout != STDOUT_FILENO && cmd->stdin != STDIN_FILENO)
	{
		while ((size = read(cmd->stdin, &buffer, sizeof(long))))
			write(cmd->stdout, &buffer, (size_t)size);
	}
}
