/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tred_lll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:45:02 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/06 13:45:03 by jeblonde         ###   ########.fr       */
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

	file = open(random_name(), O_CREAT | O_TRUNC | O_RDWR,
			dispatch->foreground.red_mode);
	if (file == -1)
	{
		dispatch->foreground.error = "Herestring failure.\n";
		return ;
	}
	write(file, src, ft_strlen(src));
	free(src);
	if (def == -1 || def == STDIN_FILENO)
		dispatch->foreground.collection.ctask->stdin = file;
	else if (def == STDOUT_FILENO)
		dispatch->foreground.collection.ctask->stdout = file;
	else
		dispatch->foreground.collection.ctask->stderr = file;
}

void					tred_lll(t_dispatch *const dispatch, int def)
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
