/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:05:31 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/07 10:05:33 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void					signal_window(int signal)
{
	t_dispatch *const	dispatch = get_dispatch(NULL);
	struct winsize		win;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	(void)signal;
	dispatch->display.co = win.ws_col;
	dispatch->display.li = win.ws_row;
}
