/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:20:25 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 16:31:14 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void				*args_copy(t_dispatch *const dispatch, char **const args)
{
	size_t				size;
	char				**new;

	size = 0;
	while (args[size])
		size++;
	if (!(new = malloc(sizeof(char*) * (size + 1))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	size = 0;
	while (args[size])
	{
		new[size] = SUPER(dispatch)->string.copy(args[size]);
		size++;
	}
	new[size] = NULL;
	return (new);
}

static void				env_remove(const int state)
{
	extern char			**environ;
	static char			**save_env = NULL;

	if (!state)
	{
		save_env = environ;
		environ = malloc(sizeof(char*));
		if (!environ)
			malloc_exit();
		*environ = NULL;
	}
	else
	{
		free(environ);
		environ = save_env;
	}
}

static void				env_i(t_dispatch *const dispatch, char **const args)
{
	char **const		split = dispatch->foreground.split;
	const int			index = dispatch->foreground.index;
	void *const			task = dispatch->foreground.collection.task;
	void *const			ctask = dispatch->foreground.collection.ctask;
	void *const			ccmd = dispatch->foreground.collection.ccmd;

	env_remove(0);
	dispatch->foreground.split = args_copy(dispatch, args);
	dispatch->foreground.index = 0;
	dispatch->foreground.collection.task = NULL;
	dispatch->foreground.collection.ctask = NULL;
	dispatch->foreground.collection.ccmd = NULL;
	SUPER(dispatch)->foreground.noget(dispatch);
	SUPER(dispatch)->foreground.execute(dispatch);
	SUPER(dispatch)->foreground.destroy(dispatch);
	dispatch->foreground.split = split;
	dispatch->foreground.index = index;
	dispatch->foreground.collection.task = task;
	dispatch->foreground.collection.ctask = ctask;
	dispatch->foreground.collection.ccmd = ccmd;
	env_remove(1);
}

int						built_env(t_dispatch *const dispatch, char **argv)
{
	extern char			**environ;
	char				**ptr;

	if (*++argv)
	{
		if (**argv == '-' && *(*argv + 1) == 'i' && !*(*argv + 2) && *(argv + 1))
		{
			env_i(dispatch, argv + 1);
			return (0);
		}
	}
	if (!environ)
		return (1);
	ptr = environ;
	while (*ptr)
	{
		write(STDOUT_FILENO, *ptr, ft_strlen(*ptr));
		write(STDOUT_FILENO, "\n", 1);
		ptr++;
	}
	return (0);
}
