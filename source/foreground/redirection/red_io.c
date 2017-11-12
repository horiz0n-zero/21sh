/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:54:08 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/06 13:32:25 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				red_io(t_dispatch *const dispatch, int def)
{
	int				fd;

	if (!SPLIT)
	{
		dispatch->foreground.error = NO_PATH_PROVIDED;
		return ;
	}
	fd = open(SPLIT, O_RDWR | O_APPEND | O_CREAT,
			dispatch->foreground.red_mode);
	if (fd == -1)
	{
		ft_vasprintf(&dispatch->foreground.error, RED_OPENF, SPLIT);
		dispatch->foreground.error_required_free = 1;
		return ;
	}
	karray(dispatch->foreground.split, dispatch->foreground.index, true);
	if (def == -1 || def == STDIN_FILENO)
		dispatch->foreground.collection.ccmd->stdin = fd;
	else if (def == STDOUT_FILENO)
		dispatch->foreground.collection.ccmd->stdout = fd;
	else
		dispatch->foreground.collection.ccmd->stderr = fd;
}
