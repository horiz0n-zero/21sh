/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:11:06 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/08 14:26:15 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int			g_type[256] =
{
	['&'] = 1,
	['|'] = 1,
	[';'] = 1,
	['<'] = 2,
	['>'] = 2,
	[']'] = 4 | 16,
	['`'] = 4 | 32,
	['}'] = 8,
	[')'] = 8
};

static const t_redfunc		functions[] =
{
	[TYPE_R] = red_r,
	[TYPE_RR] = red_rr,
	[TYPE_L] = red_l,
	[TYPE_LL] = red_ll,
	[TYPE_LLL] = red_lll,
	[TYPE_AR] = red_ar,
	[TYPE_LA] = red_la,
	[TYPE_IO] = red_io,
	[TYPE_RA] = red_ar,
	[TYPE_AL] = red_la
};

static const t_redfunc		task_functions[] =
{
	[TYPE_R] = tred_r,
	[TYPE_RR] = tred_rr,
	[TYPE_L] = tred_l,
	[TYPE_LL] = tred_ll,
	[TYPE_LLL] = tred_lll,
	[TYPE_AR] = tred_ar,
	[TYPE_LA] = tred_la,
	[TYPE_IO] = tred_io,
	[TYPE_RA] = tred_ar,
	[TYPE_AL] = tred_la
};

void						foreground_task_redirections(t_dispatch *const dispatch)
{
	int						type;
	int						number;

	number = -1;
	if (*SPLIT >= '0' && *SPLIT <= '9' && SPLITP(1) &&
			g_type[(int)*SPLITP(1)] & 2)
	{
		number = ft_atoi(SPLIT);
		karray(dispatch->foreground.split, dispatch->foreground.index, true);
	}
	if (SPLIT && (g_type[(int)*SPLIT] & 2 ||
				(g_type[(int)*SPLIT] & 1 && g_type[(int)*(SPLIT + 1)] & 2)))
	{
		if (!(type = isoftype(SPLIT)))
		{
			ft_vasprintf(&dispatch->foreground.error, BAD_OPERATOR, SPLIT);
			dispatch->foreground.error_required_free = 1;
			return ;
		}
		karray(dispatch->foreground.split, dispatch->foreground.index, true);
		task_functions[type](dispatch, number);
	}
}

void						foreground_redirections(t_dispatch *const dispatch)
{
	int						type;
	int						number;

	number = -1;
	if (*SPLIT >= '0' && *SPLIT <= '9' && SPLITP(1) &&
			g_type[(int)*SPLITP(1)] & 2)
	{
		number = ft_atoi(SPLIT);
		karray(dispatch->foreground.split, dispatch->foreground.index, true);
	}
	if (SPLIT && (g_type[(int)*SPLIT] & 2 ||
				(g_type[(int)*SPLIT] & 1 && g_type[(int)*(SPLIT + 1)] & 2)))
	{
		if (!(type = isoftype(SPLIT)))
		{
			ft_vasprintf(&dispatch->foreground.error, BAD_OPERATOR, SPLIT);
			dispatch->foreground.error_required_free = 1;
			return ;
		}
		karray(dispatch->foreground.split, dispatch->foreground.index, true);
		functions[type](dispatch, number);
	}
}
