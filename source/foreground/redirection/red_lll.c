/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_lll.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:22:04 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 17:44:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static char				*get_txt(t_dispatch *const dispatch)
{
	static const char	txt[] = "here string > ";
	static const size_t	size = sizeof(txt);

	dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1);
	if (!dispatch->display.buffer)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	dispatch->display.indes = size;
	dispatch->display.index = 0;
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	write(STDOUT_FILENO, txt, size);
	SUPER(dispatch)->display.tmp_loop(dispatch);
	return (SUPER(dispatch)->string.copy(dispatch->display.buffer));
}

static void				*random_name(void)
{
	static char			buffy[256];
	char				*ptr;
	static char			c = '0';
	int					i;

	ptr = buffy;
	*ptr++ = '/';
	*ptr++ = 't';
	*ptr++ = 'm';
	*ptr++ = 'p';
	*ptr++ = '/';
	*ptr++ = '.';
	*ptr++ = c++;
	*ptr++ = '_';
	if (c > '9')
		c = '0';
	i = 0;
	while (i++ < 9)
		*ptr++ = "ABC*EF0123456789"[(int)arc4random_uniform(16)];
	*ptr = 0;
	return (buffy);
}

static void				prepare_result(t_dispatch *const dispatch, int def,
		char *src)
{
	int					file;
	const char *const	name = random_name();

	file = open(name, O_CREAT | O_TRUNC | O_RDWR,
			dispatch->foreground.red_mode);
	if (file == -1)
	{
		dispatch->foreground.error = "Herestring failure.\n";
		return ;
	}
	write(file, src, ft_strlen(src));
	free(src);
	close(file);
	file = open(name, O_RDONLY);
	if (def == -1 || def == STDIN_FILENO)
		dispatch->foreground.collection.ccmd->stdin = file;
	else if (def == STDOUT_FILENO)
		dispatch->foreground.collection.ccmd->stdout = file;
	else
		dispatch->foreground.collection.ccmd->stderr = file;
}

void					red_lll(t_dispatch *const dispatch, int def)
{
	char				*src;
	char				*full;
	char				*tmp;

	full = NULL;
	if (!SPLIT)
	{
		dispatch->foreground.error = "herestring required a world.";
		return ;
	}
	while (1)
	{
		src = get_txt(dispatch);
		if (!ft_strcmp(src, SPLIT))
		{
			prepare_result(dispatch, def, full ? full : src);
			break ;
		}
		else
		{
			if (!full)
				full = src;
			else
			{
				tmp = full;
				full = ft_strjoin(full, src);
				free(tmp);
				free(src);
			}
		}
	}
	karray(dispatch->foreground.split, dispatch->foreground.index, true);
}
