/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astrpush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 10:33:33 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/02 14:59:53 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				astrpush(const char *src, char *dst, int index)
{
	const int		i = index;
	const size_t	len = ft_strlen(src);

	if (dst[index])
	{
		while (dst[index])
			index++;
		while (i <= index)
		{
			index--;
			dst[(size_t)index + len] = dst[index];
		}
	}
	while (*src)
		*(dst++ + i) = *src++;
}
