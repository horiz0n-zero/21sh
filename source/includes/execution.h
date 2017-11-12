/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:32:35 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/10 10:50:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>

typedef struct		s_fdptr
{
	int				fd;
	int				todo;
	char			*ptr;
}					t_fdptr;

typedef struct		s_sl
{
	const char		*s;
	size_t			l;
}					t_sl;

# define CAT_QUOTES 1
# define CAT_QUOTES_FREE 2
# define CAT_SEP 4
# define CAT_RED 8
# define CAT_PRET 16
# define CAT_SUBSHELL 32
# define CAT_STOP 64
# define CAT_SKULLBRACKETS 128
# define CAT_CROCHET 256
# define CAT_SPECTASK 512

int				isoftype(const char *const src);

# define TYPE_ERROR 0
# define TYPE_AND 1
# define TYPE_ANDAND 2
# define TYPE_OR 3
# define TYPE_OROR 4
# define TYPE_COMMA 5
# define TYPE_R 6 // >
# define TYPE_RR 7
# define TYPE_L 8 // <
# define TYPE_LL 9
# define TYPE_LLL 10
# define TYPE_AR 11 // &>
# define TYPE_LA 12 // <&
# define TYPE_IO 13
# define TYPE_RA 14 // >&
# define TYPE_AL 15 // &<

# define NORETURN __attribute__ ((noreturn))

# define NO_PATH_PROVIDED "no path provided.\n"
# define ILLEGAL_START "illegal start : %s.\n"
# define ILLEGAL_SUBSHELL "illegal subshell placement.\n"
# define RED_LA_NEED ">& redirection required a path or a number before -.\n"
# define RED_LA_BAD_MOVE "moving file descriptor : bad syntax.\n"
# define RED_DRIGHT "can't open %s for reading.\n"
# define RED_REQ_PATH "redirection required a valid path.\n"
# define ODD_INIBIT "odd error during `CMDS` process %p\n"
# define RED_OPENF "No such file or directory %s.\n"
# define REQ_MALLOC "Memory allocation failure.\n"
# define BAD_OPERATOR "Bad operator %s.\n"
# define UNK_COMMAND "command not found : %s\n"
# define BAD_COMMA "Bad comma separator.\n"
# define FATAL_EXECVE "Fatal error : execve failure.\n%s -- %p\n"
# define FATAL_FORK "Fatal error : fork failure.\n%s\n"
# define FATAL_PIPE "Fatal error : pipe failure.\n%s\n"
# define REQ_QUOTES "quotes \'%c\'> "
# define REQ_QUOTES_SIZE 12
# define BAD_BG_PERCENT "the index given by %s doesn't correspond to any job\n"

typedef struct		s_parse
{
	int				type;
	int				intype;
}					t_parse;

typedef struct		s_glob
{
	char			*content;
	void			*next;
}					t_glob;

typedef struct		s_bg
{
	pid_t			pid;
	int				status;
	# define IS_STOPPED 2
	# define IS_RUNNING 4
	int				number;
	int				pad;
	char			**argv;
}					t_bg;

typedef struct		s_cmd
{
	pid_t			pid;
	pid_t			pad;
	int				stdin;
	int				stdout;
	int				stderr;
	int				type;
	# define CMD_OK 0
	# define CMD_RED 1
	# define CMD_BUILT 2
	int				typeoff;
	int				isdone;
	void			*func;
	char			**argv;
	struct s_cmd	*next;
}					t_cmd;
void				*new_cmd(void);

typedef struct		s_task
{
	int				type;
	# define TASK_COMMON 0
	# define TASK_SUBSHELL 1
	# define TASKI_AND 2
	# define TASKI_ANDAND 4
	# define TASKI_OR 8
	# define TASKI_OROR 16
	# define TASKI_COMMA 32
	int				stdin;
	int				stdout;
	int				stderr;
	pid_t			group;
	pid_t			process;
	t_cmd			*cmd;
	struct s_task	*next;
}					t_task;
void				*new_task(void);

#endif
