/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 10:08:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/06 13:32:39 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void	red_r_close(t_dispatch *const dispatch, const int def, const int fd)
{
	if (def == -1 || def == STDOUT_FILENO)
	{
		if (dispatch->foreground.collection.ccmd->stdout != STDOUT_FILENO)
			close(dispatch->foreground.collection.ccmd->stdout);
		dispatch->foreground.collection.ccmd->stdout = fd;
	}
	else if (def == 0)
	{
		if (dispatch->foreground.collection.ccmd->stdin != STDIN_FILENO)
			close(dispatch->foreground.collection.ccmd->stdin);
		dispatch->foreground.collection.ccmd->stdin = fd;
	}
	else
	{
		if (dispatch->foreground.collection.ccmd->stderr != STDERR_FILENO)
			close(dispatch->foreground.collection.ccmd->stderr);
		dispatch->foreground.collection.ccmd->stderr = fd;
	}
}

void		red_r(t_dispatch *const dispatch, int def)
{
	int		fd;

	if (!SPLIT)
	{
		dispatch->foreground.error = RED_REQ_PATH;
		return ;
	}
	fd = open(SPLIT, O_WRONLY | O_CREAT | O_TRUNC,
			dispatch->foreground.red_mode);
	if (fd == -1)
	{
		ft_vasprintf(&dispatch->foreground.error, RED_OPENF, SPLIT);
		dispatch->foreground.error_required_free = 1;
	}
	red_r_close(dispatch, def, fd);
	karray(dispatch->foreground.split, dispatch->foreground.index, true);
}
