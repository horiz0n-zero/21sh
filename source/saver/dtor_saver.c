/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_saver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 11:41:24 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/19 14:21:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				dtor_saver(t_dispatch *const dispatch)
{
	t_saved_txt		*ptr;

	if ((ptr = dispatch->saver.first))
	{
		while (ptr)
		{
			free(ptr->buffer);
			ptr = ptr->next;
		}
	}
}
