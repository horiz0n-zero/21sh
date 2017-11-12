/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_disown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:01:18 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/04 11:25:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int		built_disown(t_dispatch *const dispatch, char **argv)
{
	(void)dispatch;
	(void)argv;
	write(STDOUT_FILENO, "soon ...\n", 9);
	return (0);
}
