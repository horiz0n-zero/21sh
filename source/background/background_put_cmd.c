/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_put_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:28:09 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 09:50:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			*background_copy_argv(t_dispatch *const dispatch, t_cmd *const cmd)
{
	char			**new;
	size_t			count;
	char			**ptr;

	count = 0;
	ptr = cmd->argv;
	while (*ptr)
	{
		ptr++;
		count++;
	}
	if (!(new = malloc(sizeof(char*) * (count + 1))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ptr = cmd->argv;
	while (*ptr)
		*new++ = SUPER(dispatch)->string.copy(*ptr++);
	*new = NULL;
	return (new - count);
}

static inline void	background_print_and(t_dispatch *const dispatch, t_cmd *const cmd)
{
	char			**argv;

	ft_printf("\33[38;5;69m< %zd >> &\33[38;5;117m\t",
			dispatch->foreground.background.array_count + 1);
	argv = cmd->argv;
	while (*argv)
		ft_printf("%s ", *argv++);
	write(STDOUT_FILENO, "\n\33[37m", sizeof("\n\33[37m"));
}


void				background_put_cmd(t_dispatch *const dispatch, t_cmd *const cmd, const int status)
{
	t_bg			*bg;

	if (!(bg = malloc(sizeof(t_bg))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	if (status & IS_RUNNING) // & start else z stop
	{
		dispatch->foreground.wait = WNOHANG;
		background_print_and(dispatch, cmd);
		dispatch->foreground.background.turn = 1;
	}
	else
		bg->pid = cmd->pid; // special case ctr - z no other things ... :-)
	dispatch->foreground.background.pointee_pid = &bg->pid;
	bg->number = (int)dispatch->foreground.background.array_count + 1;
	bg->status = status;
	bg->argv = background_copy_argv(dispatch, cmd);
	SUPER(dispatch)->foreground.background.append(dispatch, bg);
	ft_fprintf(dispatch->debug, "background append : %s\n", *bg->argv);
}
