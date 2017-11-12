/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:38:07 by afeuerst          #+#    #+#             */
/*   Updated: 2017/08/23 13:38:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void 	ft_fprintfEndFunction(const char *const src, t_printinfo *const info){
	write((int)info->data, src, info->total_len - 1);
}

void		ft_fprintf(const int fd, const char *format, ...)
{
	static t_printdata	*element = NULL;
	t_printinfo		 	info_default =
	{
		&element,
		NULL,
		(void*)ft_fprintfEndFunction,
		1,
		(uint64_t)fd
	};
	t_printinfo 		info;
	va_list 			args;

	va_start(args, format);
	info = info_default;
	info.args = &args;
	printf_exec(format, &info, info.first_element);
	va_end(args);
}
