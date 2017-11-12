/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:55:41 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 15:21:49 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_parse	g_type[256] =
{
	['|'] = {CAT_SEP, 0},
	['&'] = {CAT_SEP, 0},
	[';'] = {CAT_SEP, 0},
	['>'] = {CAT_RED, 1},
	['<'] = {CAT_RED, 1},
	['\''] = {CAT_QUOTES, 0},
	['\"'] = {CAT_QUOTES | CAT_QUOTES_FREE, 0},
	['}'] = {CAT_QUOTES | CAT_SKULLBRACKETS, 4},
	[']'] = {CAT_QUOTES | CAT_CROCHET, 2},
	[')'] = {CAT_QUOTES | CAT_SUBSHELL | CAT_SPECTASK, 4},
	['`'] = {CAT_QUOTES | CAT_PRET | CAT_SPECTASK, 4}
};

static inline void		extra_task(t_dispatch *const dispatch, const int type)
{
	if (type & CAT_SKULLBRACKETS)
	{
		SUPER(dispatch)->foreground.collection.append(dispatch, new_task());
		SUPER(dispatch)->foreground.get_shell(dispatch);
	}
	else if (type & CAT_SUBSHELL)
	{
		SUPER(dispatch)->foreground.collection.append(dispatch, new_task());
		SUPER(dispatch)->foreground.get_subshell(dispatch);
	}
	else
		SUPER(dispatch)->foreground.get_inibit(dispatch, NULL);
}

static void				get_args(t_dispatch *const dispatch)
{
	const int			type = g_type[(int)*SPLIT].intype;

	if (type & 4)
	{
		extra_task(dispatch, g_type[(int)*SPLIT].type);
		return ;
	}
	else if (!(type & 2))
	{
		if (dispatch->foreground.need_task ||
				!dispatch->foreground.collection.task)
		{
			dispatch->foreground.need_task = false;
			SUPER(dispatch)->foreground.collection.append(dispatch, new_task());
		}
		SUPER(dispatch)->foreground.collection.append_cmd(dispatch, new_cmd());
	}
	if (!type)
	{
		SUPER(dispatch)->foreground.perfom(dispatch);
		SUPER(dispatch)->foreground.get_exec(dispatch);
		SUPER(dispatch)->foreground.get_argv(dispatch);
	}
	else if (type & 2)
		SUPER(dispatch)->foreground.insert(dispatch, 16);
	else
		SUPER(dispatch)->foreground.get_argv(dispatch);
}

void					foreground_noget(t_dispatch *const dispatch)
{
	if (!dispatch->foreground.split)
		return ;
	while (SPLIT)
	{
		while (SPLIT && g_type[(int)*SPLIT].type == CAT_SEP)
		{
			if (isoftype(SPLIT) != TYPE_COMMA)
			{
				ft_vasprintf(&dispatch->foreground.error, BAD_OPERATOR, SPLIT);
				dispatch->foreground.error_required_free = 1;
				return ;
			}
			karray(dispatch->foreground.split, dispatch->foreground.index, 1);
		}
		if (SPLIT)
			get_args(dispatch);
		if (dispatch->foreground.error)
			break ;
	}
}

void					foreground_get(t_dispatch *const dispatch)
{
	dispatch->foreground.split = SUPER(dispatch)->string.split_cmd(dispatch);
	if (!dispatch->foreground.split)
		return ;
	while (SPLIT)
	{
		while (SPLIT && g_type[(int)*SPLIT].type == CAT_SEP)
		{
			if (isoftype(SPLIT) != TYPE_COMMA)
			{
				ft_vasprintf(&dispatch->foreground.error, BAD_OPERATOR, SPLIT);
				dispatch->foreground.error_required_free = 1;
				return ;
			}
			karray(dispatch->foreground.split, dispatch->foreground.index, 1);
		}
		if (SPLIT)
			get_args(dispatch);
		if (dispatch->foreground.error)
			break ;
	}
}
