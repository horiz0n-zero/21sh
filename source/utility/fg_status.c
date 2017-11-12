/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 12:48:05 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/13 12:53:06 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		fg_status(void)
{
	ft_printf("process    %hhd\n", getpid());
	ft_printf("group      %hhd\n", getpgrp());
	ft_printf("foreground %hhd\n", tcgetpgrp(STDIN_FILENO));
	ft_printf("parent     %hhd\n", getppid());
	ft_printf("parent grp %hhd\n", getpgid(getppid()));
}
