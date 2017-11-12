/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:00:06 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 12:45:30 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			background_foreground(t_dispatch *const dispatch, t_bg *const bg)
{
	extern int		errno;
	const pid_t		pid = bg->pid;

	if (bg->status & IS_STOPPED)
		kill(bg->pid, SIGCONT);
	else
	{
		setpgid(bg->pid, dispatch->foreground.background.self_group);
	}
	ft_fprintf(dispatch->debug, "fg : %s\naction : %s\n",
			*bg->argv, bg->status & IS_STOPPED ? "kill sigcont" : "setpgid");

	waitpid(bg->pid, &dispatch->foreground.status, WUNTRACED);

	ft_fprintf(dispatch->debug, "fg : no long wait now %d pid : %d\n",
			dispatch->foreground.status, pid);
}

int					built_fg(t_dispatch *const dispatch, char **argv)
{
	int				n;
	t_bg			*bg;

	if (*++argv)
		n = SUPER(dispatch)->string.atoi(*argv + 1) - 1;
	else
		n = (int)dispatch->foreground.background.array_count - 1;
	if (n < 0)
		n = 0;
	if (!dispatch->foreground.background.array_count ||
			n >= (int)dispatch->foreground.background.array_count)
	{
		if (*argv)
			ft_printf("fg: %s: no such job\n", *argv);
		else
			write(STDOUT_FILENO, "fg : no current job\n", 20);
		return (0);
	}
	bg = dispatch->foreground.background.array[n];
	background_foreground(dispatch, bg);
	return (0);
}
