/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:35:28 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/08 14:18:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int			g_type[256] =
{
	['&'] = 1,
	['|'] = 1,
	[';'] = 1,
	['<'] = 2,
	['>'] = 2,
	[']'] = 4 | 16,
	['`'] = 4 | 32,
	['}'] = 8,
	[')'] = 8
};

static void					add_separator(t_dispatch *const dispatch)
{
	int						type;

	type = isoftype(SPLIT);
	if (!type)
	{
		ft_vasprintf(&dispatch->foreground.error, BAD_OPERATOR, SPLIT);
		dispatch->foreground.error_required_free = true;
		return ;
	}
	else
	{
		dispatch->foreground.collection.ccmd->typeoff = type;
		karray(dispatch->foreground.split, dispatch->foreground.index, true);
	}
}

static void					add_argv(t_dispatch *const dispatch, size_t count,
							const int start)
{
	char					**new;

	dispatch->foreground.index = start;
	if (!(new = malloc(sizeof(char*) * (count + 2))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	*new = (void*)dispatch->foreground.collection.ccmd->argv;
	dispatch->foreground.collection.ccmd->argv = new++;
	dispatch->foreground.collection.ccmd->isdone = true;
	while (count-- > 0)
	{
		SUPER(dispatch)->foreground.perfom(dispatch);
		*new++ = SPLIT;
		dispatch->foreground.index++;
	}
	*new = NULL;
	if (SPLIT && g_type[(int)*SPLIT] & 1)
		add_separator(dispatch);
}

void						foreground_get_argv(t_dispatch *const dispatch)
{
	size_t					count;
	int						type;
	const int				start = dispatch->foreground.index;

	count = 0;
	while (SPLIT)
	{
		SUPER(dispatch)->foreground.redirections(dispatch);
		if (!SPLIT || dispatch->foreground.error)
			break ;
		if (*SPLIT >= '0' && *SPLIT <= '9' && SPLITP(1) &&
				g_type[(int)*SPLITP(1)] & 2)
			continue ;
		type = g_type[(int)*SPLIT];
		if (!type)
			count++;
		else if (type & (1 | 8))
			break ;
		else if (type & 4)
		{
			SUPER(dispatch)->foreground.insert(dispatch, type);
			continue ;
		}
		else if (type & 2)
			continue ;
		dispatch->foreground.index++;
	}
	add_argv(dispatch, count, start);
}
