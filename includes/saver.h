/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saver.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 11:40:12 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/19 14:32:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAVER_H
# define SAVER_H

# define CMD_SAVE 3
# include <unistd.h>

typedef struct	s_saved_txt
{
	char		*buffer;
	size_t		buffer_size;
	size_t		index;
	size_t		len;
	void		*next;
	void		*prev;
}				t_saved_txt;

#endif
