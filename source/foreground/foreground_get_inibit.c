/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_get_inibit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 10:34:25 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 09:52:47 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void				*random_name(void)
{
	static char			buffer[42];
	char				*ptr;
	int					i;

	i = 0;
	ptr = buffer;
	*ptr++ = '/';
	*ptr++ = 't';
	*ptr++ = 'm';
	*ptr++ = 'p';
	*ptr++ = '/';
	*ptr++ = '.';
	while (i < 10)
	{
		*ptr++ = "0123456789ABCD#F"[(int)arc4random_uniform(16)];
		i++;
	}
	*ptr = 0;
	return (buffer);
}

static void				insert_result(t_dispatch *const dispatch,
		const char *file, char ***new)
{
	struct stat			chat;
	char				*content;
	char				**split;
	const int			fd = open(file, O_RDWR);

	if (stat(file, &chat) || fd == -1)
	{
		dispatch->foreground.error = "stat failure.";
		return ;
	}
	if (!(content = malloc((size_t)chat.st_size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	read(fd, content, (size_t)chat.st_size);
	*(content + chat.st_size) = 0;
	split = SUPER(dispatch)->string.split(content);
	if (split)
		*new = split;
	free(content);
	close(fd);
}

static void				execute_inibit(t_dispatch *const dispatch,
		char ***const new)
{
	pid_t				pid;
	int					file;
	char *const			name = random_name();
	t_task				*task;

	if (!(pid = fork()))
	{
		file = open(name, O_CREAT | O_TRUNC | O_RDWR,
				dispatch->foreground.red_mode);
		task = dispatch->foreground.collection.task;
		while (task)
		{
			task->stdout = file;
			task = task->next;
		}
		SUPER(dispatch)->foreground.execute(dispatch);
		SUPER(dispatch)->foreground.destroy(dispatch);
		exit(dispatch->foreground.status);
	}
	else if (pid == -1)
		ft_printf(FATAL_FORK, "in `inibiter command`.");
	else
	{
		waitpid(pid, &dispatch->foreground.status, dispatch->foreground.wait);
		insert_result(dispatch, name, new);
	}
}

void					foreground_get_inibit(t_dispatch *const dispatch,
		char **new)
{
	char **const		split = dispatch->foreground.split;
	const int			index = dispatch->foreground.index;
	char *const			buffer = dispatch->display.buffer;
	const size_t		buffer_size = dispatch->display.buffer_size;
	const size_t		len = dispatch->display.len;
	void *const			ctask = dispatch->foreground.collection.ctask;
	void *const			ccmd = dispatch->foreground.collection.ccmd;
	void *const			task = dispatch->foreground.collection.task;

	dispatch->display.len = ft_strlen(SPLIT + 1);
	while (dispatch->display.buffer_size < dispatch->display.len)
		dispatch->display.buffer_size *= 2;
	if (!(dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	ft_memmove(dispatch->display.buffer, SPLIT + 1, dispatch->display.len);
	karray(dispatch->foreground.split, dispatch->foreground.index, true);
	dispatch->foreground.index = 0;
	dispatch->foreground.need_task = false;
	dispatch->foreground.collection.task = NULL;
	dispatch->foreground.collection.ctask = NULL;
	dispatch->foreground.collection.ccmd = NULL;
	SUPER(dispatch)->foreground.get(dispatch);
	if (!dispatch->foreground.error)
		execute_inibit(dispatch, &new);
	free(dispatch->foreground.split);
	free(dispatch->display.buffer);
	dispatch->foreground.split = split;
	dispatch->foreground.index = index;
	dispatch->display.len = len;
	dispatch->display.buffer = buffer;
	dispatch->display.buffer_size = buffer_size;
	dispatch->foreground.need_task = false;
	dispatch->foreground.collection.ctask = ctask;
	dispatch->foreground.collection.ccmd = ccmd;
	dispatch->foreground.collection.task = task;
	if (new)
	{
		arrayinsert(dispatch, new);
		free(new);
	}
}
