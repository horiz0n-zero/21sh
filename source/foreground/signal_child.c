/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:57:49 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/10 10:18:07 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void				child_crash(t_bg *const bg, const int index,
		const int signal, t_dispatch *const dis)
{
	char				**argv;

	if (index >= 23)
		return ;
	ft_printf("\r\33[38;05;214m>> %d > \33[37m\33[38;05;196m%s\t",
			(int)bg->pid, dis->foreground.background.errors[signal]);
	argv = bg->argv;
	while (*argv)
		ft_printf("%s ", *argv++);
	write(STDOUT_FILENO, "\33[37m\n", sizeof("\33[37m\n"));
}

static void				child_terminated(t_bg *const bg)
{
	char				**argv;

	ft_printf("\r\33[38;05;69m<< %d >\t\33[38;05;75mdone\t", bg->number);
	argv = bg->argv;
	while (*argv)
		ft_printf("%s ", *argv++);
	write(STDOUT_FILENO, "\33[37m\n", sizeof("\33[37m\n"));
}

void					signal_child(int signal)
{
	pid_t				pid;
	t_bg				*bg;
	t_dispatch *const	dispatch = get_dispatch(NULL);
	int					index;

	if ((pid = waitpid(-1, &signal, WNOHANG)) > 0)
	{
		bg = SUPER(dispatch)->foreground.background.find(dispatch, pid, &index);
		if (bg)
		{
			if (WIFEXITED(signal))
				child_terminated(bg);
			else if (WIFSIGNALED(signal))
				child_crash(bg, index + 1, WTERMSIG(signal), dispatch);
			//else if (WIFSTOPPED(signal))
			//	return ;
			ft_fprintf(dispatch->debug, "signal child %s removed \n", bg->argv[0]);
			SUPER(dispatch)->foreground.background.remove(dispatch, index);
		}
	}
}
