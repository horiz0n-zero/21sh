/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_saver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 11:40:50 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/19 14:11:42 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		ctor_saver(t_dispatch *const dispatch)
{
	dispatch->saver.count = 0;
	dispatch->saver.current = NULL;
	dispatch->saver.first = NULL;
}
