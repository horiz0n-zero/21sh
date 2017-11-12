/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 08:52:55 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/09 09:17:12 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void		colors_usage(void)
{
	static const char	*usages[] =
	{
		"\33[38;5;196mc\33[38;5;197mo\33[38;5;198mlo\33[38;5;199mr\33[38;5;200ms : \n",
		"\33[38;5;82m -c show current color.\n"
	};
	static const size_t	sizes[] =
	{
		sizeof("\33[38;5;196mc\33[38;5;197mo\33[38;5;198mlo\33[38;5;199mr\33[38;5;200ms : \n"),
		sizeof("\33[38;5;92m -c show current color.\n")
	};

	write(STDOUT_FILENO, usages[0], sizes[0]);
	write(STDOUT_FILENO, usages[1], sizes[1]);
}

static inline void		colors_show_colors(t_dispatch *const dispatch)
{
	static const char	txt[] = "location color : %scolor\n" \
								"separator color : %scolor\n" \
								"separator string : %s\n" \
								"prompt color : %scolor\n" \
								"prompt string : %s\n" \
								"text color : %s color\n" \
								"builtins color : %s color\n";

	ft_printf(txt, dispatch->display.properties.location_color,
			dispatch->display.properties.separator_color,
			dispatch->display.properties.separator_string,
			dispatch->display.properties.prompt_color,
			dispatch->display.properties.prompt_string,
			dispatch->display.properties.text_color,
			dispatch->display.properties.builtins_color);
}

int						built_colors(t_dispatch *const dispatch, char **argv)
{
	if (*++argv)
	{
		if (**argv == '-')
		{
			if (*(*argv + 1) == 'c')
				colors_show_colors(dispatch);
		}
	}
	else
		colors_usage();
	return (0);
}
