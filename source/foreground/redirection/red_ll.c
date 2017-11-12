/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:23:13 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 15:31:10 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static char				*get_txt(t_dispatch *const dispatch)
{
	static const size_t	size = sizeof("heredoc > ");
	char *const			buffer = dispatch->display.buffer;
	const size_t		buffer_size = dispatch->display.buffer_size;
	const size_t		len = dispatch->display.len;
	char				*ptr;

	dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1);
	if (!dispatch->display.buffer)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	dispatch->display.indes = size;
	dispatch->display.index = 0;
	dispatch->display.len = 0;
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	write(STDOUT_FILENO, "heredoc > ", size);
	SUPER(dispatch)->display.tmp_loop(dispatch);
	ptr = SUPER(dispatch)->string.copy(dispatch->display.buffer);
	free(dispatch->display.buffer);
	dispatch->display.buffer = buffer;
	dispatch->display.buffer_size = buffer_size;
	dispatch->display.len = len;
	return (ptr);
}

static void				*random_name(void)
{
	static char			buffy[256];
	char				*ptr;
	int					i;

	ptr = buffy;
	*ptr++ = '/';
	*ptr++ = 't';
	*ptr++ = 'm';
	*ptr++ = 'p';
	*ptr++ = '/';
	*ptr++ = '.';
	i = 0;
	while (i++ < 15)
		*ptr++ = "ABC*EF0123456789"[(int)arc4random_uniform(16)];
	*ptr = 0;
	return (buffy);
}

static void				prepare_result(t_dispatch *const dispatch, int def,
		char *src)
{
	int					file;
	char *const			name = random_name();

	file = open(name, O_CREAT | O_TRUNC | O_RDWR,
			dispatch->foreground.red_mode);
	if (file == -1)
	{
		dispatch->foreground.error = "Heredoc failure.\n";
		return ;
	}
	write(file, src, ft_strlen(src));
	free(src);
	close(file);
	file = open(name, O_RDONLY);
	if (def == -1 || def == STDIN_FILENO)
	{
		if (dispatch->foreground.collection.ccmd->stdin != STDIN_FILENO)
			close(dispatch->foreground.collection.ccmd->stdin);
		dispatch->foreground.collection.ccmd->stdin = file;
	}
	else if (def == STDOUT_FILENO)
	{
		if (dispatch->foreground.collection.ccmd->stdout != STDOUT_FILENO)
			close(dispatch->foreground.collection.ccmd->stdout);
		dispatch->foreground.collection.ccmd->stdout = file;
	}
	else
	{
		if (dispatch->foreground.collection.ccmd->stderr != STDERR_FILENO)
			close(dispatch->foreground.collection.ccmd->stderr);
		dispatch->foreground.collection.ccmd->stderr = file;
	}
}

void					red_ll(t_dispatch *const dispatch, int def)
{
	char				*src;
	char				*full;
	char				*tmp;

	full = NULL;
	if (!SPLIT)
	{
		dispatch->foreground.error = "heredoc required a world.\n";
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
