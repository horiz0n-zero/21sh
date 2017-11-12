/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:55:06 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/09 13:47:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	jobs_print(const t_bg *const bg)
{
	char			**argv;

	argv = bg->argv;
	ft_printf("\33[38;5;75m<< %d >> %s\t", (int)bg->pid,
			bg->status & IS_STOPPED ?
			"\33[38;5;166mstopped\33[38;5;117m" : "\33[38;5;118mrunning\33[38;5;117m");
	while (*argv)
		ft_printf("%s ", *argv++);
	write(STDOUT_FILENO, "\n\33[37m", sizeof("\n\33[37m"));
}

int					built_jobs(t_dispatch *const dispatch, char **argv)
{
	size_t			count;
	t_bg			*bg;

	(void)argv;
	count = 0;
	if (!dispatch->foreground.background.array_count)
		write(STDOUT_FILENO, "No jobs\n", sizeof("No jobs\n"));
	while (count < dispatch->foreground.background.array_count)
	{
		bg = dispatch->foreground.background.array[count++];
		jobs_print(bg);
	}
	return (0);
}
