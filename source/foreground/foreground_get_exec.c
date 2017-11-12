/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:49:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 09:50:11 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static int				get_hash(t_dispatch *const dispatch)
{
	void				*e;

	e = SUPER(dispatch)->foreground.builtins.get(dispatch, SPLIT);
	if (e)
	{
		dispatch->foreground.collection.ccmd->type = CMD_BUILT;
		dispatch->foreground.collection.ccmd->func = e;
		dispatch->foreground.collection.ccmd->argv = (void*)SPLIT;
		dispatch->foreground.index++;
		return (0);
	}
	e = SUPER(dispatch)->foreground.binaries.get(dispatch, SPLIT);
	if (e)
	{
		dispatch->foreground.collection.ccmd->type = CMD_OK;
		dispatch->foreground.collection.ccmd->argv = e;
		karray(dispatch->foreground.split, dispatch->foreground.index, true);
		return (0);
	}
	e = SUPER(dispatch)->foreground.alias.get(dispatch, SPLIT);
	if (e)
	{
		karray(dispatch->foreground.split, dispatch->foreground.index, true);
		arrayinsert(dispatch, (e = SUPER(dispatch)->string.arraycopy(e)));
		free(e);
		foreground_get_exec(dispatch);
		return (0);
	}
	return (1);
}

void					foreground_get_exec(t_dispatch *const dispatch)
{
	struct stat			chat;

	if (!dispatch->foreground.collection.ccmd)
		return ;
	if (!get_hash(dispatch))
		return ;
	else if (!stat(SPLIT, &chat) && chat.st_mode & S_IFREG && chat.st_mode &
			S_IXUSR)
	{
		dispatch->foreground.collection.ccmd->type = CMD_OK;
		dispatch->foreground.collection.ccmd->argv = (void*)SPLIT;
		dispatch->foreground.index++;
	}
	else
	{
		ft_vasprintf(&dispatch->foreground.error, UNK_COMMAND, SPLIT);
		dispatch->foreground.error_required_free = 1;
		karray(dispatch->foreground.split, dispatch->foreground.index, true);
	}
}
