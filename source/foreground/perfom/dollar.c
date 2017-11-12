/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:01:32 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 10:20:45 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				*dollar_push(t_dispatch *const dispatch, char **src,
		char *dst)
{
	char			*ptr;
	char			*tmp;
	char			buffy;

	tmp = *src + 1;
	while (*tmp >= 'A' && *tmp <= 'Z')
		tmp++;
	buffy = *tmp;
	*tmp = 0;
	ptr = SUPER(dispatch)->env.get(dispatch, *src + 1);
	*src = tmp;
	*tmp = buffy;
	if (!ptr)
		return (dst);
	while (*ptr)
		*dst++ = *ptr++;
	return (dst);
}

size_t				dollar_len(t_dispatch *const dispatch, char **src)
{
	char			*tmp;
	char			*ptr;
	char			buffy;

	tmp = *src + 1;
	while (*tmp >= 'A' && *tmp <= 'Z')
		tmp++;
	buffy = *tmp;
	*tmp = 0;
	ptr = SUPER(dispatch)->env.get(dispatch, *src + 1);
	*src = tmp;
	*tmp = buffy;
	if (!ptr)
		return (0);
	return (ft_strlen(ptr));
}
