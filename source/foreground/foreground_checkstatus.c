/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_checkstatus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:43:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 12:46:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	status_signaled(t_dispatch *const dispatch, t_cmd *const cmd)
{
	int				err;
	char			**argv;

	err = WTERMSIG(dispatch->foreground.status);
	if (err >= 23)
		err = SIGQUIT;
	ft_printf("\r\33[38;5;208m>> \33[38;5;196m%s\t\33[37m",
			dispatch->foreground.background.errors[err]);
	argv = cmd->argv;
	while (*argv)
		ft_printf("%s ", *argv++);
	write(STDOUT_FILENO, "\n", 1);
}

static inline void	status_stopped(t_dispatch *const dispatch, t_cmd *const cmd)
{
	char			**argv;

	SUPER(dispatch)->foreground.background.put_cmd(dispatch, cmd, IS_STOPPED);
	write(STDOUT_FILENO, "\r\33[38;5;69m>> \33[38;5;166mstopped >\33[38;5;123m\t",
			sizeof("\r\33[38;5;69m>> \33[38;5;166mstopped \33[38;5;123m>\t"));
	argv = cmd->argv;
	while (*argv)
		ft_printf("%s ", *argv++);
	write(STDOUT_FILENO, "\n\33[37m", sizeof("\n\33[37m"));
}

int					foreground_checkstatus(t_dispatch *const dispatch, t_cmd *const cmd)
{
	if (cmd->typeoff)
	{
		if (cmd->typeoff == TYPE_ANDAND
				&& WEXITSTATUS(dispatch->foreground.status))
			return (1);
		if (cmd->typeoff == TYPE_OROR
				&& !WEXITSTATUS(dispatch->foreground.status))
			return (1);
		if (cmd->typeoff == TYPE_AND)
			dispatch->foreground.wait = WUNTRACED;
	}
	if (WIFSIGNALED(dispatch->foreground.status))
		status_signaled(dispatch, cmd);
	if (WIFSTOPPED(dispatch->foreground.status))
		status_stopped(dispatch, cmd);
	return (0);
}
