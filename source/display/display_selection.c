/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 11:32:02 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 12:56:21 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				display_selection(t_dispatch *const dispatch)
{
	ft_fprintf(dispatch->debug, ">> selection ready %p\n", &dispatch->display.select);
}
