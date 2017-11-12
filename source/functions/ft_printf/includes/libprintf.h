/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:37:55 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/17 12:15:58 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPRINTF_H
# define LIBPRINTF_H

# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/_types/_wchar_t.h>

# ifndef bool
#  define true  (int)1
#  define false (int)0
#  define bool int
# endif

int						ft_printf(const char *format, ...);
void 					ft_fprintf(const int fd, const char *format, ...);
void 					ft_vasprintf(char **dst, const char *format, ...);

typedef struct 			s_printdata	t_printdata;

struct 					s_printdata
{
	int64_t				data;
	uint64_t 			len;
	uint64_t			width;
	uint64_t			precision;
	uint32_t			conversion;
	uint32_t 			end_index;
	uint32_t			flags;
	uint32_t 			lenght;
	t_printdata 		*next;
};

typedef struct 			s_printinfo t_printinfo;

struct					s_printinfo
{
	void 				*first_element;
	va_list 			*args;
	void 				*function;
	uint64_t			total_len;
	uint64_t			data;
};

# define MINUS 1
# define PLUS 2
# define SPACE 4
# define ZERO 8
# define HASH 16
# define POINT 32

# define PRINT_ERROR 0
# define PRINT_PERCENT 1
# define PRINT_S 2 // s
# define PRINT_SS 3 // S
# define PRINT_P 4
# define PRINT_D 5 // d
# define PRINT_DD 6 // D
# define PRINT_I 7
# define PRINT_O 8 // o
# define PRINT_OO 9 // O
# define PRINT_U 10 // u
# define PRINT_UU 11 // U
# define PRINT_X 12 // x
# define PRINT_XX 13 // X
# define PRINT_C 14 // c
# define PRINT_CC 15 // C

void 					printf_exec(const char *const src, t_printinfo *const info, t_printdata **next);

void 					printf_get_data(const char *const src, uint32_t *const index, t_printdata *data);

typedef void 			(*const lenght_func)(t_printdata *data, va_list *args);
void					lenght_percent(t_printdata *data, va_list *args);
void					lenght_void(t_printdata *data, va_list *args);
void 					lenght_string(t_printdata *data, va_list *args);
void 					lenght_pointer(t_printdata *data, va_list *args);
void 					lenght_int(t_printdata *data, va_list *args);
void 					lenght_int_long(t_printdata *data, va_list *args);
void 					lenght_octal(t_printdata *data, va_list *args);
void 					lenght_octal_long(t_printdata *data, va_list *args);
void 					lenght_uint(t_printdata *data, va_list *args);
void 					lenght_uint_long(t_printdata *data, va_list *args);
void 					lenght_hexa(t_printdata *data, va_list *args);
void 					lenght_unicode(t_printdata *data, va_list *args);
void 					lenght_unicode_string(t_printdata *data, va_list *args);

typedef void 			(*const transform_func)(t_printdata *data, char *dst);
void 					transform_unicode_string(t_printdata *data, char *dst);
void 					transform_unicode(t_printdata *data, char *dst);
void 					transform_hexa_lower(t_printdata *data, char *dst);
void 					transform_hexa_upper(t_printdata *data, char *dst);
void 					transform_uint(t_printdata *data, char *dst);
void 					transform_int(t_printdata *data, char *dst);
void					transform_percent(t_printdata *data, char *dst);
void					transform_void(t_printdata *data, char *dst);
void 					transform_string(t_printdata *data, char *dst);
void 					transform_pointer(t_printdata *data, char *dst);
void 					transform_octal(t_printdata *data, char *dst);
void 					transform_char(t_printdata *data, char *dst);

// utility
uint32_t				atoi_print(uint64_t *const value, const char *const src, uint32_t index);
#endif
