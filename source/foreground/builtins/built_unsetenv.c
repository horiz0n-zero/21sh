/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:25:40 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 10:18:38 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int						built_unsetenv(t_dispatch *const dispatch, char **argv)
{
	static const char	*usage[] =
	{
		"unsetenv [arguments ...]\n",
		"unsetenv will remove every argument in the environement.\n",
		"arguments format : VALUE\33[37m\n"
	};
	static const size_t	usage_size[] =
	{
		sizeof("unsetenv [arguments ...]\n"),
		sizeof("unsetenv will remove every argument in the environement.\n"),
		sizeof("arguments format : VALUE\33[37m\n")
	};

	if (*++argv)
		while (*argv)
			SUPER(dispatch)->env.remove(dispatch, *argv++);
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
	return (0);
}
