/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:07:27 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/07 10:21:18 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

size_t				home_len(t_dispatch *const dispatch, char **src)
{
	char *const		ptr = SUPER(dispatch)->env.get(dispatch, "HOME");

	*src = *src + 1;
	if (!ptr)
		return (0);
	return (ft_strlen(ptr));
}

void				*home_push(t_dispatch *const dispatch, char **src,
		char *dst)
{
	char			*ptr;

	ptr = SUPER(dispatch)->env.get(dispatch, "HOME");
	*src = *src + 1;
	if (!ptr)
		return (dst);
	while (*ptr)
		*dst++ = *ptr++;
	return (dst);
}
