/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:38:20 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/17 18:31:47 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void 				ft_printfEndFunction(const char *const src, t_printinfo *const info)
{
	info->total_len--;
	info->data = (uint64_t)write(STDOUT_FILENO, src, info->total_len);
}

int 						ft_printf(const char *format, ...)
{
	static t_printdata 		*element = NULL;
	static t_printinfo 		info_default =
	{
		&element,
		NULL,
		(void*)ft_printfEndFunction,
		1, // total len + '\0'
		0
	};
	t_printinfo 			info;
	va_list 				args;

	info = info_default;
	va_start(args, format);
	info.args = &args;
	printf_exec(format, &info, info.first_element);
	va_end(args);
	return ((int)info.total_len);
}
