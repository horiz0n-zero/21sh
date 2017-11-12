/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:22:59 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/09 13:53:25 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_cmd	g_cmd =
{
	-1,
	0,
	STDIN_FILENO,
	STDOUT_FILENO,
	STDERR_FILENO,
	CMD_RED,
	0,
	0,
	NULL,
	NULL,
	NULL
};

void				*new_cmd(void)
{
	t_cmd			*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		malloc_exit();
	*cmd = g_cmd;
	return (cmd);
}
