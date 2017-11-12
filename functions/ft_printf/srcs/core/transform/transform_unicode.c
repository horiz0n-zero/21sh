/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_unicode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:42:11 by afeuerst          #+#    #+#             */
/*   Updated: 2017/08/23 13:42:12 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void					transform_unicode(t_printdata *data, char *dst)
{
	char 				*unicode = (void*)&data->data;

	while (data->lenght-- > 0)
		*dst++ = *unicode++;
}
