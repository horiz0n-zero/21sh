/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 12:01:31 by afeuerst          #+#    #+#             */
/*   Updated: 2017/09/20 11:38:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				red_l(t_dispatch *const dispatch, int def)
{
	int				fd;

	if (!SPLIT)
	{
		dispatch->foreground.error = RED_REQ_PATH;
		return ;
	}
	fd = open(SPLIT, O_RDONLY, dispatch->foreground.red_mode);
	if (fd == -1)
	{
		ft_vasprintf(&dispatch->foreground.error, RED_OPENF, SPLIT);
		dispatch->foreground.error_required_free = 1;
	}
	karray(dispatch->foreground.split, dispatch->foreground.index, true);
	if (def == -1 || def == STDIN_FILENO)
		dispatch->foreground.collection.ccmd->stdin = fd;
	else if (def == STDOUT_FILENO)
		dispatch->foreground.collection.ccmd->stdout = fd;
	else
		dispatch->foreground.collection.ccmd->stderr = fd;
}
