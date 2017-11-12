/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split_cmd_count.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 13:37:28 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/03 10:07:54 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const char			g_split[256] =
{
	[';']= 1,
	['&'] = 1,
	['|'] = 1,
	['>'] = 1,
	['<'] = 1,
	[' '] = 2,
	['\n'] = 2,
	['\t'] = 2,
	['`'] = '`',
	['['] = ']',
	['{'] = '}',
	['('] = ')',
	['\''] = '\'',
	['\"'] = '\"'
};

static inline void			string_special(t_dispatch *const dispatch,
		int *const index, const char raw)
{
	if (BUFFER(*index) && raw == 1)
		while (BUFFER(*index) && g_split[(int)BUFFER(*index)] == 1)
			*index = *index + 1;
	else if (raw > '!')
	{
		while (1)
		{
			while (BUFFER(*index) && BUFFER(*index) != raw)
				*index = *index + 1;
			if (BUFFER(*index) && BUFFER(*index) == raw &&
					(*index = *index + 1))
				break ;
			else
				SUPER(dispatch)->display.getsplit(dispatch, raw);
		}
	}
}

size_t						string_split_cmd_count(t_dispatch *const dispatch,
		int index)
{
	register size_t			count;
	register char			raw;

	count = 1;
	while (BUFFER(index))
	{
		while (BUFFER(index) && g_split[(int)BUFFER(index)] == 2)
			index++;
		if (BUFFER(index) && !g_split[(int)BUFFER(index)])
		{
			count++;
			while (BUFFER(index) && !g_split[(int)BUFFER(index)])
				index++;
		}
		else if (BUFFER(index) && (raw = g_split[(int)BUFFER(index)]) &&
				++index)
		{
			count++;
			string_special(dispatch, &index, raw);
		}
	}
	return (count);
}
