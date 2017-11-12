#include "libprintf.h"
#include <stdlib.h>

static void 			ft_vasprintf_endfunc(const char *const src, t_printinfo *const info)
{
	char 				*new;
	int 				index;

	index = 0;
	new = malloc(sizeof(char) * info->total_len);
	while (index < (int)info->total_len)
	{
		new[index] = src[index];
		index++;
	}
	new[info->total_len] = 0;
	info->data = (uint64_t)new;
}

void					ft_vasprintf(char **dst, const char *format, ...)
{
	static t_printdata	*element = NULL;
	static t_printinfo info_default =
	{
		&element,
		NULL,
		(void*)ft_vasprintf_endfunc,
		1,
		0
	};
	t_printinfo 		info;
	va_list 			args;

	info = info_default;
	va_start(args, format);
	info.args = &args;
	printf_exec(format, &info, info.first_element);
	va_end(args);
	*dst = (char*)info.data;
}
