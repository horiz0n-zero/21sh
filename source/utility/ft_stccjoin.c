/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stccjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 09:46:10 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/17 09:47:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			*ft_stccjoin(const char *s1, const char *s2, const char c)
{
	static char	stc[1024];
	char		*ptr;

	ptr = stc;
	while (*s1)
		*ptr++ = *s1++;
	*ptr++ = c;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = 0;
	return (stc);
}
