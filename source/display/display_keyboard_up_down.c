#include "purplegreensh.h"

//TODO: FIX BROKEN HISTORY

void	display_up(t_dispatch *const dispatch)
{
	(void)dispatch;
/*//	int i;

//	if (dispatch->saver.current && dispatch->saver.current->prev)
//	{
//		SUPER(dispatch)->display.home(dispatch);
//		while (dispatch->display.len > 0)
//			SUPER(dispatch)->display.remove(dispatch);
//		ft_memset(dispatch->display.buffer, dispatch->display.buffer_size);
//		ft_memmove(dispatch->display.buffer, dispatch->saver.current->buffer,
//				   				   dispatch->saver.current->len);
//		i = -1;
//		while (dispatch->display.buffer[++i])
//			SUPER(dispatch)->display.append(dispatch->display.buffer[i], dispatch);


//		ft_memmove(dispatch->display.buffer, dispatch->saver.current->buffer,
//				   dispatch->saver.current->len);
//		SUPER(dispatch)->display.start_line(dispatch);
//		ft_printf("%s%s", dispatch->display.caps[SC].s, dispatch->display.caps[CD].s);
//		dispatch->display.index = 0;
//		dispatch->display.len = dispatch->saver.current->len;
//		write(STDOUT_FILENO, dispatch->display.buffer, dispatch->display.len);
//		write(STDOUT_FILENO, dispatch->display.caps[RC].s, dispatch->display.caps[RC].l);
//		dispatch->saver.current = dispatch->saver.current->prev;
//	}*/
}

void			display_down(t_dispatch *const dispatch)
{
	(void)dispatch;
/*	int i;

//	if (dispatch->saver.current && dispatch->saver.current->next)
//	{
//		SUPER(dispatch)->display.home(dispatch);
//		while (dispatch->display.len > 0)
//			SUPER(dispatch)->display.remove(dispatch);
//		dispatch->saver.current = dispatch->saver.current->next;
//		ft_memset(dispatch->display.buffer, dispatch->display.buffer_size);
//		ft_memmove(dispatch->display.buffer, dispatch->saver.current->buffer,
//					dispatch->saver.current->len);
//		i = -1;
//		while (dispatch->display.buffer[++i])
//			SUPER(dispatch)->display.append(dispatch->display.buffer[i], dispatch);
//		SUPER(dispatch)->display.start_line(dispatch);
//		ft_printf("%s%s", dispatch->display.caps[SC].s, dispatch->display.caps[CD].s);
//		dispatch->display.index = 0;
//		dispatch->display.len = dispatch->saver.current->len;
//		write(STDOUT_FILENO, dispatch->display.buffer, dispatch->display.len);
//		write(STDOUT_FILENO, dispatch->display.caps[RC].s, dispatch->display.caps[RC].l);
//	}
*/}

void			display_line_up(t_dispatch *const dispatch)
{
	int delta;

	delta = (int)dispatch->display.index - (int)dispatch->display.co;
	if (delta >= 0)
	{
		delta = (int)dispatch->display.co;
		while (delta--)
			SUPER(dispatch)->display.left(dispatch);
	}
}

void			display_line_down(t_dispatch *const dispatch)
{
	int delta;

	delta = (int)dispatch->display.index + (int)dispatch->display.co;
	if (delta <= (int)dispatch->display.len)
	{
		delta = (int)dispatch->display.co;
		while (delta--)
			SUPER(dispatch)->display.right(dispatch);
	}
}
