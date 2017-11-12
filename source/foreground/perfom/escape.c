/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:30:43 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/06 13:32:05 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const char	g_escape_cor[256] =
{
	['\\'] = '\\',
	['\"'] = '\"',
	['\''] = '\'',
	['e'] = '\33',
	['n'] = '\n',
	['v'] = '\v',
	['r'] = '\r',
	['t'] = '\t',
	['b'] = '\b',
	['f'] = '\f',
	['a'] = '\a'
};

size_t				escape_len(t_dispatch *const dispatch, char **src)
{
	char			*ptr;

	(void)dispatch;
	ptr = *src + 1;
	if (g_escape_cor[(int)*ptr])
	{
		*src = ptr + 1;
		return (1);
	}
	else if (*ptr >= '0' && *ptr <= '9')
	{
		while (*ptr >= '0' && *ptr <= '9')
			ptr++;
		*src = ptr;
		return (1);
	}
	else
	{
		*src = ptr;
		return (1);
	}
}

void				*escape_push(t_dispatch *const dispatch, char **src,
		char *dst)
{
	char			*ptr;
	int				n;

	(void)dispatch;
	ptr = *src + 1;
	if (g_escape_cor[(int)*ptr])
	{
		*dst++ = g_escape_cor[(int)*ptr++];
		*src = ptr;
		return (dst);
	}
	else if (*ptr >= '0' && *ptr <= '9')
	{
		n = 0;
		while (*ptr >= '0' && *ptr <= '9')
			n = n * 10 + (*ptr++ - 48);
		*dst++ = (char)n;
		*src = ptr;
		return (dst);
	}
	else
	{
		*src = ptr;
		*dst++ = '\\';
		return (dst);
	}
}
