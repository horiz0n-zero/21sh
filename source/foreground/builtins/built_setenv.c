/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:28:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/09 08:38:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int						built_setenv(t_dispatch *const dispatch, char **argv)
{
	extern char			**environ;

	static const char	*usage[] =
	{
		"setenv [arguments...]\n",
		"setenv will add every argument to the environement.\n",
		"arguments format : NAME VALUE.\n"
	};
	static size_t		usage_size[] =
	{
		sizeof("setenv [arguments...]\n"),
		sizeof("setenv will add every argument to the environement.\n"),
		sizeof("arguments format : NAME=VALUE.\n")
	};

	argv++;
	if (*argv && *(argv + 1))
	{
		while (1)
		{
			SUPER(dispatch)->env.append(dispatch, *argv, *(argv + 1));
			argv += 2;
			if (*argv && *(argv + 1))
				continue ;
			else
				break ;
		}
	}
	else
	{
		write(STDERR_FILENO, dispatch->display.properties.builtins_color,
				ft_strlen(dispatch->display.properties.builtins_color));
		write(STDERR_FILENO, usage[0], usage_size[0]);
		write(STDERR_FILENO, usage[1], usage_size[1]);
		write(STDERR_FILENO, usage[2], usage_size[2]);
		return (0);
	}
	SUPER(dispatch)->foreground.binaries.dtor(dispatch);
	SUPER(dispatch)->foreground.binaries.ctor(dispatch);
	SUPER(dispatch)->env.sort((int)SUPER(dispatch)->env.count(), environ);
	return (0);
}
