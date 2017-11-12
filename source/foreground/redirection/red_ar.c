/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_ar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:35:39 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/08 14:00:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	ar_default(t_dispatch *const dispatch, const int path)
{
	if (dispatch->foreground.collection.ccmd->stdout != STDOUT_FILENO)
		close(dispatch->foreground.collection.ccmd->stdout);
	if (dispatch->foreground.collection.ccmd->stderr != STDERR_FILENO)
		close(dispatch->foreground.collection.ccmd->stderr);
	dispatch->foreground.collection.ccmd->stdout = path;
	dispatch->foreground.collection.ccmd->stderr = dup(path);
}

static inline void	ar_manage(t_dispatch *const dispatch, const int def, const int fd)
{
	if (!def && dispatch->foreground.collection.ccmd->stdin != STDIN_FILENO)
		close(dispatch->foreground.collection.ccmd->stdin);
	if ((def == -1 || def == 1) && dispatch->foreground.collection.ccmd->stdout != STDOUT_FILENO)
		close(dispatch->foreground.collection.ccmd->stdout);
	if (def == 2 && dispatch->foreground.collection.ccmd->stderr != STDERR_FILENO)
		close(dispatch->foreground.collection.ccmd->stderr);
	if (!def)
		dispatch->foreground.collection.ccmd->stdin = fd;
	else if (def == 1 || def == -1)
		dispatch->foreground.collection.ccmd->stdout = fd;
	else
		dispatch->foreground.collection.ccmd->stderr = fd;
}

void				red_ar(t_dispatch *const dispatch, int def)
{
	int				fd;
	int				minus;
	char			*ptr;

	if (SPLIT)
	{
		ptr = SPLIT;
		while (*ptr)
			ptr++;
		if (*--ptr == '-' && !(*ptr = 0))
			minus = true;
		else
			minus = false;
		fd = open(SPLIT, O_WRONLY | O_CREAT | O_TRUNC,
				dispatch->foreground.red_mode);
		if (fd == -1)
		{
			ft_vasprintf(&dispatch->foreground.error, RED_DRIGHT, SPLIT);
			dispatch->foreground.error_required_free = true;
			return ;
		}
		if (def == -1 && !minus)
			ar_default(dispatch, fd);
		else
			ar_manage(dispatch, def, fd);
		karray(dispatch->foreground.split, dispatch->foreground.index, true);
		return ;
	}
	dispatch->foreground.error = NO_PATH_PROVIDED;
}
