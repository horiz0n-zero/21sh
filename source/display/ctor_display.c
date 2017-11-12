/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:37 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/09 08:58:02 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_properties	default_properties =
{
	.location_color = "\33[38;5;21m",
	.separator_string = "<<",
	.separator_color = "\33[38;5;163m",
	.prompt_string = ">",
	.prompt_color = "\33[38;5;161m",
	.text_color = "\33[37m",
	.builtins_color = "\33[38;05;226m"
};

static void					display_got_capacities(t_dispatch *const dispatch,
		...)
{
	va_list					args;
	char					*cap;
	int						index;

	index = 0;
	va_start(args, dispatch);
	while ((cap = va_arg(args, char*)))
	{
		if (tgetflag(cap) || !(dispatch->display.caps[index].s =
					tgetstr(cap, NULL)))
			SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
		dispatch->display.caps[index].l =
			ft_strlen(dispatch->display.caps[index].s);
		index++;
	}
	va_end(args);
}

static void					display_set_termios(t_dispatch *const dispatch)
{
	struct winsize			win;

	ft_memset((char*)&dispatch->display.current, sizeof(struct termios));
	dispatch->display.current.c_iflag |= (IGNPAR | IXOFF | IXON);
	dispatch->display.current.c_oflag |= (ONLCR | OPOST);
	dispatch->display.current.c_lflag |= ISIG;
	dispatch->display.current.c_cc[VMIN] = 1;
	dispatch->display.current.c_cc[VTIME] = 0;
	//dispatch->display.current.c_cc[VINTR] = 3; // ctrl c
	// if (ioctl(STDIN_FILENO, TCGETA, &dispatch->display.saved) == -1)
	if (tcgetattr(STDIN_FILENO, &dispatch->display.saved) == -1)
		SUPER(dispatch)->exit(dispatch, "No struct termios available.");
	//if (ioctl(STDIN_FILENO, TCSAFLUSH, &dispatch->display.current) == -1)
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &dispatch->display.current) == -1)
		SUPER(dispatch)->exit(dispatch, "Can't set the termios struct.");
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win) == -1)
		SUPER(dispatch)->exit(dispatch, "Can't get the screen size.");
	dispatch->display.co = (size_t)win.ws_col;
	dispatch->display.li = (size_t)win.ws_row;
	dispatch->display.work = WORKD_MAIN;
}

void						ctor_display(t_dispatch *const dispatch)
{
	dispatch->display.properties = default_properties;
	if (uname(&dispatch->display.node))
		ft_memmove((void*)dispatch->display.node.nodename, "???", 3);
	if (tgetent(NULL, SUPER(dispatch)->env.get(dispatch, "TERM")) == -1)
		SUPER(dispatch)->exit(dispatch, "termcaps library not found.");
	display_got_capacities(dispatch, "cr", "le", "nd", "up", "do",
				"bl", "rc", "sc", "cl", "cd", "ce", "dc", "vi", "ve",
				"ti", "te", "al", "cm", "vb", "ho", "ch", NULL);
	display_set_termios(dispatch);
	dispatch->display.index = 0;
	dispatch->display.len = 0;
	dispatch->display.buffer_size = 2;
	//ft_printf("%s%s", CAPS(TI).s, CAPS(CL).s);
	dispatch->display.buffer = malloc(sizeof(char) *
			(dispatch->display.buffer_size + 1));
	if (!dispatch->display.buffer)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.pasteboard = NULL;
	SUPER(dispatch)->display.prompt(NULL, 0, dispatch);
}
