/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_perfom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:01:29 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/07 10:03:00 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static int				perfom_quote(t_dispatch *const dispatch, char **src)
{
	char				*tmp;
	const int			isfree = **src == '\'' ? 1 : 0;

	tmp = *src;
	*src = SUPER(dispatch)->string.copy(tmp + 1);
	free(tmp);
	if (isfree)
		SPLIT = *src;
	return (isfree);
}

static const t_perfom	g_perfoms[256] =
{
	['$'] = {1, dollar_len, dollar_push},
	['\\'] = {1, escape_len, escape_push},
	['~'] = {1, home_len, home_push}
};

static void				foreground_push(t_dispatch *const dispatch, char *src,
		const size_t size)
{
	char				*new;

	if (!(new = malloc(size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	while (*src)
	{
		if (g_perfoms[(int)*src].index)
		{
			new = g_perfoms[(int)*src].func_push(dispatch, &src, new);
		}
		else
			*new++ = *src++;
	}
	*new = 0;
	SPLIT = new - size;
}

void					foreground_perfom(t_dispatch *const dispatch)
{
	char				*src;
	size_t				size;
	char				*save;

	src = dispatch->foreground.split[dispatch->foreground.index];
	if (*src == '\'' || *src == '\"')
		if (perfom_quote(dispatch, &src))
			return ;
	save = src;
	size = 0;
	while (*src)
	{
		if (g_perfoms[(int)*src].index)
		{
			size += g_perfoms[(int)*src].func_len(dispatch, &src);
		}
		else
		{
			src++;
			size++;
		}
	}
	foreground_push(dispatch, save, size);
	free(save);
}
