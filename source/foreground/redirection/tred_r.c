/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tred_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:40:27 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/06 13:42:29 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		tred_r(t_dispatch *const dispatch, int def)
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
	if (def == -1 || def == STDOUT_FILENO)
		dispatch->foreground.collection.ctask->stdout = fd;
	else if (def == 0)
		dispatch->foreground.collection.ctask->stdin = fd;
	else
		dispatch->foreground.collection.ctask->stderr = fd;
	karray(dispatch->foreground.split, dispatch->foreground.index, true);
}
