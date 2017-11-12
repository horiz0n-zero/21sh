/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saver_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 13:19:47 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/20 11:19:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void		saver_push(t_dispatch *const dispatch, void **const pos, void *const prev)
{
	t_saved_txt *const	new = malloc(sizeof(t_saved_txt));

	if (!new)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	new->buffer = dispatch->display.buffer;
	new->buffer_size = dispatch->display.buffer_size;
	new->index = dispatch->display.index;
	new->len = dispatch->display.len;
	new->next = NULL;
	new->prev = prev;
	*pos = new;
}

void					saver_save(t_dispatch *const dispatch)
{
	t_saved_txt			*saved;

	dispatch->saver.count++;
	if (!dispatch->saver.first)
	{
		saver_push(dispatch, (void*)&dispatch->saver.first, NULL);
		dispatch->saver.current = dispatch->saver.first;
	}
	else
	{
		saved = dispatch->saver.current;
		while (saved->next)
			saved = saved->next;
		saver_push(dispatch, (void*)&saved->next, saved);
		dispatch->saver.current = saved->next;
	}
}
