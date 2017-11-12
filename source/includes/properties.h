/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:33:10 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 11:37:21 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROPERTIES_H
# define PROPERTIES_H

# include <unistd.h>

typedef struct		s_properties
{
	const char		*location_color;

	const char		*separator_string;
	const char		*separator_color;

	const char		*prompt_string;
	const char		*prompt_color;

	const char		*text_color;
	const char		*builtins_color;
}					t_properties;

typedef struct		s_select
{
	char			*name;
	const char		*bg;
	const char		*fg;
	int				selected;
	int				pad;
}					t_select;

typedef struct		s_selection
{
	t_select		*array;
	size_t			count;
	size_t			len;
}					t_selection;

# define CAP_COUNT 21
# define CR 0
# define LE 1
# define ND 2
# define UP 3
# define DO 4
# define BL 5
# define RC 6
# define SC 7
# define CL 8
# define CD 9
# define CE 10
# define DC 11
# define VI 12
# define VE 13
# define TI 14
# define TE 15
# define AL 16
# define CM 17
# define VB 18
# define HO 19
# define CH 20

# define TCGETS		0x5401
# define TCSETS		0x5402
# define TCSETSW	0x5403
# define TCSETSF	0x5404
# define TCGETA		0x5405
# define TCSETA		0x5406
# define TCSETAW	0x5407
# define TCSETAF	0x5408
# define TCSBRK		0x5409
# define TCXONC		0x540A
# define TCFLSH		0x540B

#endif
