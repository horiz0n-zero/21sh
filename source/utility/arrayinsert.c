/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrayinsert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:31:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/09/20 15:42:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static size_t			array_count(char **array)
{
	size_t				count;

	count = 0;
	while (array[count])
		count++;
	return (count);
}

void					arrayinsert(t_dispatch *const dispatch, char **insert)
{
	const size_t		dis_size = array_count(dispatch->foreground.split);
	const size_t		in_size = array_count(insert);
	char				**new;
	int					i;
	int					index;

	i = 0;
	index = dispatch->foreground.index;
	if (!(new = malloc(sizeof(char*) * (dis_size + in_size + 1))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	while (i < index)
	{
		new[i] = dispatch->foreground.split[i];
		i++;
	}
	while (*insert)
		new[i++] = *insert++;
	while (dispatch->foreground.split[index])
		new[i++] = dispatch->foreground.split[index++];
	new[i] = NULL;
	free(dispatch->foreground.split);
	dispatch->foreground.split = new;
}
