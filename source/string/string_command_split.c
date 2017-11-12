/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_command_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 13:31:50 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 16:33:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const char	g_split[256] =
{
	[';'] = 1,
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

static char			*ft_cmd_spec(t_dispatch *const dispatch, int *const index)
{
	int				size;
	char			*new;

	size = 0;
	while (BUFFER(size + *index) && g_split[(int)BUFFER(size + *index)] & 1)
		size++;
	if (!(new = malloc((size_t)size + 3)))
		return (NULL);
	size = 0;
	while (BUFFER(size + *index) && g_split[(int)BUFFER(size + *index)] & 1)
	{
		new[size] = BUFFER(size + *index);
		size++;
	}
	new[size] = 0;
	*index = *index + size;
	return (new);
}

static char			*ft_cmd_zero(t_dispatch *const dispatch, int *const index)
{
	int				i;
	char			*new;

	i = 0;
	while (BUFFER(i + *index) && !g_split[(int)BUFFER(i + *index)])
		i++;
	if (!(new = malloc((size_t)(i + 1))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	i = 0;
	while (BUFFER(i + *index) && !g_split[(int)BUFFER(i + *index)])
	{
		new[i] = BUFFER(i + *index);
		i++;
	}
	new[i] = 0;
	*index = *index + i;
	return (new);
}

static char			*ft_cmd_quotes(t_dispatch *const dispatch, int *const index,
		const char raw)
{
	int				size;
	char			*new;

	size = 1;
	while (BUFFER(size + *index) && BUFFER(size + *index) != raw)
		size++;
	if (!(new = malloc((size_t)size + 1)))
		return (NULL);
	size = 0;
	new[size++] = raw;
	while (BUFFER(size + *index) && BUFFER(size + *index) != raw)
	{
		new[size] = BUFFER(size + *index);
		size++;
	}
	new[size] = 0;
	*index = *index + size + 1;
	return (new);
}

static void			debug_list(t_dispatch *const dispatch, char **str)
{
	write(dispatch->debug, "> ", 2);
	while (*str)
	{
		ft_fprintf(dispatch->debug, "[ %s ]", *str++);
	}
	write(dispatch->debug, "\n", 1);
}

char				**string_split_cmd(t_dispatch *const dispatch)
{
	char			**ptr;
	const size_t	count =
		SUPER(dispatch)->string.split_cmd_count(dispatch, 0);
	char			raw;
	int				index;

	index = 0;
	if (!(ptr = malloc(sizeof(char*) * count)))
		return (NULL);
	while (BUFFER(index))
	{
		while (BUFFER(index) && g_split[(int)BUFFER(index)] == 2)
			index++;
		if (BUFFER(index) && !g_split[(int)BUFFER(index)])
			*ptr++ = ft_cmd_zero(dispatch, &index);
		else if (BUFFER(index) && (raw = g_split[(int)BUFFER(index)]))
		{
			if (raw > '!')
				*ptr++ = ft_cmd_quotes(dispatch, &index, raw);
			else
				*ptr++ = ft_cmd_spec(dispatch, &index);
		}
	}
	*ptr = NULL;
	debug_list(dispatch, ptr - count + 1);
	return (ptr - count + 1);
}
