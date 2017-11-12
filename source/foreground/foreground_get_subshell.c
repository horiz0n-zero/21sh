/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_get_subshell.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:57:05 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/08 14:25:00 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int			g_reaction[256] =
{
	['&'] = 1,
	['|'] = 1,
	[';'] = 1,
	['>'] = 2,
	['<'] = 2
};

static void					foreground_subshell_argv(t_dispatch *const dispatch)
{
	register int			type;
	static const int		typecor[6] =
	{
		[TYPE_AND] = TASKI_AND,
		[TYPE_ANDAND] = TASKI_ANDAND,
		[TYPE_OR] = TASKI_OR,
		[TYPE_OROR] = TASKI_OROR,
		[TYPE_COMMA] = TASKI_COMMA
	};

	type = 0;
	while (SPLIT)
	{
		SUPER(dispatch)->foreground.task_redirections(dispatch);
		if (!SPLIT)
			break ;
		type = g_reaction[(int)*SPLIT];
		if (type & 2)
			continue ;
		else
			break ;
	}
	if (SPLIT && type & 1)
	{
		type = isoftype(SPLIT);
		if (!(type = typecor[type]))
		{
			ft_vasprintf(&dispatch->foreground.error, BAD_OPERATOR, SPLIT);
			dispatch->foreground.error_required_free = true;
		}
		else
			karray(dispatch->foreground.split, dispatch->foreground.index,
					true);
		dispatch->foreground.collection.ctask->type |= type;
	}
}

void					foreground_get_subshell(t_dispatch *const dispatch)
{
	char **const		split = dispatch->foreground.split;
	const int			index = dispatch->foreground.index;
	char *const			buffer = dispatch->display.buffer;
	const size_t		buffer_size = dispatch->display.buffer_size;
	const size_t		len = dispatch->display.len;

	dispatch->display.len = ft_strlen(SPLIT + 1);
	while (dispatch->display.buffer_size < dispatch->display.len)
		dispatch->display.buffer_size *= 2;
	if (!(dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	ft_memmove(dispatch->display.buffer, SPLIT + 1, dispatch->display.len);
	karray(dispatch->foreground.split, dispatch->foreground.index, true);
	dispatch->foreground.collection.ctask->type = TASK_SUBSHELL;
	dispatch->foreground.index = 0;
	dispatch->foreground.need_task = false;
	SUPER(dispatch)->foreground.get(dispatch);
	free(dispatch->foreground.split);
	free(dispatch->display.buffer);
	dispatch->foreground.split = split;
	dispatch->foreground.index = index;
	foreground_subshell_argv(dispatch);
	dispatch->display.len = len;
	dispatch->display.buffer = buffer;
	dispatch->display.buffer_size = buffer_size;
	dispatch->foreground.need_task = true;
}
