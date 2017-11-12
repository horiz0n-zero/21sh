/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:39:08 by afeuerst          #+#    #+#             */
/*   Updated: 2017/09/25 13:57:29 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int				built_exit(t_dispatch *const dispatch, char **argv)
{
	(void)argv;
	SUPER(dispatch)->exit(dispatch, NULL);
	return (0);
}
