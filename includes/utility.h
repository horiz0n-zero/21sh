/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:33:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/06 13:05:20 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

# include <unistd.h>
# include "execution.h"

typedef struct s_dispatch	t_dispatch;

void		ft_memset(char *const src, size_t len);
size_t		ft_strlen(const char *str);
size_t		ft_strlen_magik(const char *str, const char wizard);
void		ft_memmove(char *dst, const char *src, size_t size);
void		ft_memmove_ll(long long *dst, const long long src, size_t size);
void		apush(char *src, const int index, const char c);
void		kpush(char *src, const int index);
t_fdptr		get_filefd(t_dispatch *const dispatch, char *src, const int flags);
char		*ft_strjoin(const char *s1, const char *s2);
int			ft_ismultipleof(size_t number, size_t of);
char		*get_fdnumber(int *const dst, char *src);
void		*get_file(const char *const path);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strsub(const char *src);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strcjoin(const char *s1, const char *s2, const char c);
void		*ft_stccjoin(const char *s1, const char *s2, const char c);
void		malloc_exit(void);
int			ft_atoi(const char *src);
void		astrpush(const char *src, char *dst, int index);

void		karray(char **split, int index, const int freed);
void		arrayinsert(t_dispatch *const dispatch, char **insert);
void		*perfom_string(t_dispatch *const dispatch, char *src);
char		**ft_simple_split(const char *src);
char		*ft_itoa(int number);

void		fg_status(void);

# define BUFFY_SIZE 128
# define SWAP(a, b) a ^= b; b ^= a; a ^= b;

#endif
