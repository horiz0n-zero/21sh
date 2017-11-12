/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 16:23:30 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 09:48:11 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		background_remove(t_dispatch *const dispatch, const int index)
{
	t_bg	*bg;
	char	**argv;

	dispatch->foreground.background.array_count--;
	bg = dispatch->foreground.background.array[index];
	ft_fprintf(dispatch->debug, "remove : %s with pid %d\n", *bg->argv, bg->pid);
	argv = bg->argv;
	while (*argv)
		free(*argv++);
	free(bg->argv);
	karray((void*)dispatch->foreground.background.array, index, true);
}
