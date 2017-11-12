/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:26:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 12:43:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			*percent_change(t_dispatch *const dispatch, const char *src)
{
	int				n;
	t_bg			*bg;

	if (!*src)
		n = 0;
	else
		n = SUPER(dispatch)->string.atoi(src) - 1;
	if (n < 0)
		n = 0;
	if (n >= (int)dispatch->foreground.background.array_count)
	{
		return (SUPER(dispatch)->string.copy("(null)"));
	}
	bg = dispatch->foreground.background.array[n];
	return (SUPER(dispatch)->string.itoa((int)bg->pid));
}

static size_t		array_count(char **argv)
{
	size_t			size;

	size = 0;
	while (argv[size])
		size++;
	return (size + 1);
}

void				*background_percent(t_dispatch *const dispatch, char **argv)
{
	char			**pargv;
	const size_t	size = array_count(argv);

	pargv = malloc(sizeof(char*) * size);
	if (!pargv)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	while (*argv)
	{
		if (**argv == '%')
			*pargv++ = percent_change(dispatch, *argv++ + 1);
		else
			*pargv++ = SUPER(dispatch)->string.copy(*argv++);
	}
	*pargv = NULL;
	return (pargv - size + 1);
}
