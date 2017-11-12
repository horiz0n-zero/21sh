/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purplegreensh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:33:21 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 15:21:12 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PURPLEGREENSH_H
# define PURPLEGREENSH_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <curses.h>
# include <term.h>
# include <sys/termios.h>
# include <sys/ioctl.h>
# include <sys/utsname.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <time.h>

# include "settings.h"
# include "libprintf.h"
# include "properties.h"
# include "utility.h"
# include "saver.h"
# include "execution.h"

typedef struct s_dispatch	t_dispatch;
typedef struct s_environ	t_environ;
typedef struct s_display	t_display;
typedef struct s_foreground	t_foreground;
typedef struct s_background	t_background;
typedef struct s_collection	t_collection;
typedef struct s_saver		t_saver;
typedef struct s_hashable	t_hashable;
typedef struct s_string		t_string;

typedef struct s_subclass_dispatch 	t_subclass_dispatch;
typedef struct s_subclass_environ 	t_subclass_environ;
typedef struct s_class_display 		t_class_display;
typedef struct s_subclass_foreground t_subclass_foreground;
typedef struct s_class_background	t_class_background;
typedef struct s_class_collection	t_class_collection;
typedef struct s_class_saver		t_class_saver;
typedef struct s_class_hashable		t_class_hashable;
typedef struct s_class_string 		t_class_string;

struct 						s_string
{
	char 						*in;
	char 						*out;
};

typedef struct					s_hashpacket
{
	void						*element;
	char						*src;
	struct s_hashpacket			*next;
}								t_hashpacket;

struct							s_hashable
{
	size_t						size;
	t_hashpacket				*packets;
};

struct							s_saver
{
	size_t						count;
	t_saved_txt					*first;
	t_saved_txt					*current;
};

struct							s_collection
{
	t_task						*task;
	t_task						*ctask;
	t_cmd						*ccmd;
};

struct							s_background
{
	pid_t						self_group;
	pid_t						execute;
	int							turn; // soluce temporaire pour le display
	int							pad;
	pid_t						*pids;
	size_t						pids_count;
	size_t						pids_size;
	t_bg						**array;
	size_t						array_count;
	size_t						array_size;
	pid_t						*pointee_pid;
	const char					**errors;
};

struct							s_foreground
{
	char						*error;
	int							error_required_free;
	int							index;
	char						**split;
	# define SPLIT dispatch->foreground.split[dispatch->foreground.index]
	# define SPLITP(i) dispatch->foreground.split[dispatch->foreground.index + i]
	# define SPLITM(i) dispatch->foreground.split[dispatch->foreground.index - i]
	int							need_task; // indicateur new task !
	short						mode_pad;
	mode_t						red_mode;
	int							status;
	int							wait;
	t_background				background;
	t_collection				collection;
	t_hashable					binaries;
	t_hashable					builtins;
	t_hashable					alias;
	char						*aliaspath;
	int							aliasfile;
	int							pad;
};

struct							s_display
{
	t_properties				properties;
	t_selection					select;
	struct utsname				node;
	struct termios				current;
	struct termios				saved;
	t_sl						caps[CAP_COUNT];
	char						*buffer;
	# define BUFFER(index) dispatch->display.buffer[index]
	size_t						buffer_size;
	size_t						index;
	size_t						indes;
	# define DISPLAY(o) SUPER(o)->display
	# define ISREDGE(o) DISPLAY(o).isredge(o->display.indes + o->display.index, \
			o->display.co)
	# define ISLEDGE(o) DISPLAY(o).isledge(o->display.indes + o->display.index, \
			o->display.co)
	# define CAPS(name) dispatch->display.caps[name]
	size_t						len;
	size_t						co;
	size_t						li;
	int							work;
	# define WORKD_MAIN 0
	# define WORKD_TXT 1
	int							table;
	char						*pasteboard;
};

struct							s_environ
{
	const void					*pad;
};

struct							s_dispatch
{
	const void					*self;
	int							debug;
	int							pad;
	t_environ					env;
	t_display					display;
	t_foreground				foreground;
	t_saver						saver;
	t_string 					string;
};

// description //
# define SUPER(dispatch) ((const t_subclass_dispatch*)(dispatch->self))

struct 							s_class_string
{
	void						*(*copy)(const char *src);
	void						*(*arraycopy)(const char **src);
	void						(*apush)(char *src, const int index, const char c);
	void						(*kpush)(char *src, const int index);
	void						*(*split)(const char *src);
	char						**(*split_cmd)(t_dispatch *const dispatch);
	size_t						(*split_cmd_count)(t_dispatch *const dispatch, int index);
	int							(*atoi)(const char *src);
	char						*(*itoa)(int n);
};
void 							*string_copy(const char *src);
void							*string_arraycopy(const char **src);
void							string_apush(char *src, const int index, const char c);
void							string_kpush(char *src, const int index);
void							*string_split(const char *src);
char							**string_split_cmd(t_dispatch *const dispatch);
size_t							string_split_cmd_count(t_dispatch *const dispatch, int index);
int								string_atoi(const char *src);
char							*string_itoa(int n);

struct							s_class_hashable
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*append)(t_dispatch *const dispatch, char *src, void *const element);
	size_t						(*key)(const char *src);
	void						*(*get)(t_dispatch *const dispatch, const char *src);
};
void							ctor_hashablebin(t_dispatch *const dispatch);
void							ctor_hashbuiltins(t_dispatch *const dispatch);
void							ctor_hashalias(t_dispatch *const dispatch);
void							dtor_hashablebin(t_dispatch *const dispatch);
void							dtor_hashbuiltins(t_dispatch *const dispatch);
void							dtor_hashalias(t_dispatch *const dispatch);

void							hashablebin_append(t_dispatch *const dispatch, char *src, void *const element);
void							hashbuiltins_append(t_dispatch *const dispatch, char *src, void *const element);
void							hashalias_append(t_dispatch *const dispatch, char *src, void *const element);

size_t							hashable_key(const char *src);

void							*hashablebin_get(t_dispatch *const dispatch, const char *src);
void							*hashbuiltins_get(t_dispatch *const dispatch, const char *src);
void							*hashalias_get(t_dispatch *const dispatch, const char *src);

struct							s_class_saver
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*save)(t_dispatch *const dispatch);
};
void							ctor_saver(t_dispatch *const dispatch);
void							dtor_saver(t_dispatch *const dispatch);
void							saver_save(t_dispatch *const dispatch);

struct							s_class_collection
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*append)(t_dispatch *const dispatch, t_task *const task);
	void						(*append_cmd)(t_dispatch *const dispatch, t_cmd *cmd);
};
void							ctor_collection(t_dispatch *const dispatch);
void							dtor_collection(t_dispatch *const dispatch);
void							collection_append(t_dispatch *const dispatch, t_task *const task);
void							collection_append_cmd(t_dispatch *const dispatch, t_cmd *cmd);

struct							s_class_background
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*append)(t_dispatch *const dispatch, void *const element);
	void						*(*get)(t_dispatch *const dispatch, const int index);
	void						*(*find)(t_dispatch *const dispatch, const pid_t pid, int *const index);
	void						(*remove)(t_dispatch *const dispatch, const int index);
	void						(*put_cmd)(t_dispatch *const dispatch, t_cmd *const cmd,
			const int status);
	void						(*append_pid)(t_dispatch *const dispatch, const pid_t pid);
	void						(*wait_pids)(t_dispatch *const dispatch);
	void						*(*percent)(t_dispatch *const dispatch, char **argv);
};
void							ctor_background(t_dispatch *const dispatch);
void							dtor_background(t_dispatch *const dispatch);
void							background_append(t_dispatch *const dispatch, void *const element);
void							*background_get(t_dispatch *const dispatch, const int index);
void							*background_find(t_dispatch *const dispatch, const pid_t pid,
													int *const index);
void							background_remove(t_dispatch *const dispatch, const int index);
void							background_put_cmd(t_dispatch *const dispatch, t_cmd *const cmd,
		const int status);
void							background_append_pid(t_dispatch *const dispatch, const pid_t pid);
void							background_wait_pids(t_dispatch *const dispatch);
void							*background_percent(t_dispatch *const dispatch, char **argv);

struct							s_subclass_foreground
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*setsignal)(const int type);
	# define DEFAULT 0
	# define IGNORE 1
	# define SELF 2
	void						(*get)(t_dispatch *const dispatch);
	void						(*noget)(t_dispatch *const dispatch);
	void						(*get_exec)(t_dispatch *const dispatch);
	void						(*get_argv)(t_dispatch *const dispatch);
	void						(*get_subshell)(t_dispatch *const dispatch);
	void						(*get_inibit)(t_dispatch *const dispatch, char **new);
	void						(*get_shell)(t_dispatch *const dispatch);
	void						(*redirections)(t_dispatch *const dispatch);
	void						(*task_redirections)(t_dispatch *const dispatch);
	void						(*perfom)(t_dispatch *const dispatch);
	void						(*insert)(t_dispatch *const dispatch, const int type);
	void						(*set_std)(t_task *const task, t_cmd *const cmd);
	int							(*checkstatus)(t_dispatch *const dispatch, t_cmd *const cmd);
	void						(*execute)(t_dispatch *const dispatch);
	void						*(*pipexec)(t_dispatch *const dispatch, t_task *const task, t_cmd *cmd);
	void						*(*taskpipexec)(t_dispatch *const dispatch, t_task *task);
	void						(*destroy)(t_dispatch *const dispatch);
	t_class_background			background;
	t_class_collection			collection;
	t_class_hashable			binaries;
	t_class_hashable			builtins;
	t_class_hashable			alias;
};
void							ctor_foreground(t_dispatch *const dispatch);
void							dtor_foreground(t_dispatch *const dispatch);
void							foreground_setsignal(const int type);
void							signal_exit(int signal);
void							signal_window(int signal);
void							signal_child(int signal);
void							foreground_get(t_dispatch *const dispatch);
void							foreground_noget(t_dispatch *const dispatch);
void							foreground_get_exec(t_dispatch *const dispatch);
void							foreground_get_argv(t_dispatch *const dispatch);
void							foreground_get_subshell(t_dispatch *const dispatch);
void							foreground_get_inibit(t_dispatch *const dispatch, char **new);
void							foreground_get_shell(t_dispatch *const dispatch);
void							foreground_redirections(t_dispatch *const dispatch);
void							foreground_task_redirections(t_dispatch *const dispatch);
void							foreground_perfom(t_dispatch *const dispatch);
void							foreground_insert(t_dispatch *const dispatch, const int type);
void							foreground_set_std(t_task *const task, t_cmd *const cmd);
int								foreground_checkstatus(t_dispatch *const dispatch, t_cmd *const cmd);
void							foreground_execute(t_dispatch *const dispatch);
void							*foreground_pipexec(t_dispatch *const dispatch, 
									t_task *const task, t_cmd *cmd);
void							*foreground_taskpipexec(t_dispatch *const dispatch, t_task *task);
void							foreground_destroy(t_dispatch *const dispatch);

struct							s_class_display
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*read_one)(const char *ptr,
			t_dispatch *const dispatch);
	void						(*read_three)(const char *ptr,
			t_dispatch *const dispatch);
	void						(*read_more)(const char *ptr,
			t_dispatch *const dispatch);
	void						(*prompt)(const char *pr, const size_t indes, t_dispatch *const dispatch);
	void						(*tmp_loop)(t_dispatch *const dispatch);
	void						(*tmp_breakloop)(t_dispatch *const dispatch);
	void						(*expand)(t_dispatch *const dispatch);
	void						(*getsplit)(t_dispatch *const dispatch, const char c);
	void						(*getstring)(t_dispatch *const dispatch, const char *str);
	void						(*select)(t_dispatch *const dispatch);
	void						(*selection)(t_dispatch *const dispatch);
	void						(*cancel)(t_dispatch *const dispatch);
	void						(*lclear)(t_dispatch *const dispatch);
	int	__attribute__ ((pure))	(*isredge)(const size_t n, const size_t of);
	int	__attribute__ ((pure))	(*isledge)(const size_t n, const size_t of);
	void						(*start_line)(t_dispatch *const dispatch);
	void						(*end_line)(t_dispatch *const dispatch);
	void						(*goposition)(const size_t pos, t_dispatch *const dispatch);
	void						(*append)(const char c, t_dispatch *const dispatch);
	void						(*remove)(t_dispatch *const dispatch);
	void						(*delete)(t_dispatch *const dispatch);
	void						(*right)(t_dispatch *const dispatch);
	void						(*left)(t_dispatch *const dispatch);
	void						(*word_left)(t_dispatch *const dispatch);
	void						(*word_right)(t_dispatch *const dispatch);
	void						(*up)(t_dispatch *const dispatch);
	void						(*down)(t_dispatch *const dispatch);
	void						(*line_up)(t_dispatch *const dispatch);
	void						(*line_down)(t_dispatch *const dispatch);
	void						(*home)(t_dispatch *const dispatch);
	void						(*end)(t_dispatch *const dispatch);
	void						(*cut)(t_dispatch *const dispatch);
	void						(*paste)(t_dispatch *const dispatch);
};

void							ctor_display(t_dispatch *const dispatch);
void							dtor_display(t_dispatch *const dispatch);
void							display_read_one(const char *ptr,
		t_dispatch *const dispatch);
void							display_read_three(const char *ptr,
		t_dispatch *const dispatch);
void							display_read_more(const char *ptr,
		t_dispatch *const dispatch);
void							display_prompt(const char *pr, const size_t indes, t_dispatch *const dispatch);
void							display_tmp_loop(t_dispatch *const dispatch);
void							display_tmp_breakloop(t_dispatch *const dispatch);
void							display_expand(t_dispatch *const dispatch);
void							display_getsplit(t_dispatch *const dispatch, const char c);
void							display_getstring(t_dispatch *const dispatch, const char *str);
void							display_select(t_dispatch *const dispatch);
void							display_selection(t_dispatch *const dispatch);
void							display_cancel(t_dispatch *const dispatch);
void							display_lclear(t_dispatch *const dispatch);
int	__attribute__ ((pure))		display_isredge(const size_t n, const size_t of);
int	__attribute__ ((pure))		display_isledge(const size_t n, const size_t of);
void							display_start_line(t_dispatch *const dispatch);
void							display_end_line(t_dispatch *const dispatch);
void							display_goposition(const size_t pos, t_dispatch *const dispatch);
void							display_append(const char c, t_dispatch *const dispatch);				//KEYBOARD
void							display_remove(t_dispatch *const dispatch);								//
void							display_delete(t_dispatch *const dispatch);								// |
void							display_left(t_dispatch *const dispatch);								// V
void							display_right(t_dispatch *const dispatch);
void							display_word_left(t_dispatch *const dispatch);
void							display_word_right(t_dispatch *const dispatch);
void							display_up(t_dispatch *const dispatch);
void							display_down(t_dispatch *const dispatch);
void							display_line_up(t_dispatch *const dispatch);
void							display_line_down(t_dispatch *const dispatch);
void							display_home(t_dispatch *const dispatch);
void							display_end(t_dispatch *const dispatch);
void							display_cut(t_dispatch *const dispatch);
void							display_paste(t_dispatch *const dispatch);								// ^

struct							s_subclass_environ
{
	void		 				(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	size_t						(*count)(void);
	void						*(*get)(t_dispatch *const dispatch, const char *name);
	void 						(*remove)(t_dispatch *const dispatch, const char *const name);
	void						(*guard)(t_dispatch *const dispatch);
	void						(*append)(t_dispatch *const dispatch, const char *name, const char *value);
	int							(*corres)(const char *name, const char *env);
	void						(*sort)(const int count, char **array);
};
void							ctor_environ(t_dispatch *const dispatch);
void							dtor_environ(t_dispatch *const dispatch);
size_t							environ_count(void);
void							*environ_get(t_dispatch *const dispatch, const char *name);
void 							environ_remove(t_dispatch *const dispatch, const char *const src);
void							environ_guard(t_dispatch *const dispatch);
void							environ_append(t_dispatch *const dispatch, const char *name, const char *value);
int								environ_corres(const char *name, const char *env);
void							environ_shell_sort(const int count, char **array);

struct							s_subclass_dispatch
{
	void						(*ctor)(t_dispatch *const dispatch, const void *const self);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*exit)(t_dispatch *const dispatch, const char *err);
	void						(*start)(t_dispatch *const dispatch);
	void						(*sleep)(const time_t secs, const long nsecs);
	t_subclass_environ			env;
	t_class_display				display;
	t_subclass_foreground		foreground;
	t_class_saver				saver;
	t_class_string				string;
};
void							ctor_dispatch(t_dispatch *const dispatch, const void *const self);
void							dtor_dispatch(t_dispatch *const dispatch);
void							dispatch_exit(t_dispatch *const dispatch, const char *err);
void							dispatch_start(t_dispatch *const dispatch);
void							dispatch_sleep(const time_t secs, const long nsecs);

void							*get_dispatch(void *const dispatch);

/* **************************** */

typedef struct					s_guard
{
	const char					*name;
	char						*(*get)(t_dispatch *const dispatch);
	char						*default_name;
}								t_guard;
char							*environ_pwd(t_dispatch *const dispatch);
char 							*environ_home(t_dispatch *const dispatch);

typedef int						(*builtfunc)(t_dispatch *const dispatch, char **argv);
int								built_env(t_dispatch *const dispatch, char **argv);
int								built_unsetenv(t_dispatch *const dispatch, char **argv);
int								built_setenv(t_dispatch *const dispatch, char **argv);
int								built_cd(t_dispatch *const dispatch, char **argv);
int								built_echo(t_dispatch *const dispatch, char **argv);
int								built_exit(t_dispatch *const dispatch, char **argv);
int 							built_clear(t_dispatch *const dispatch, char **argv);
int								built_jobs(t_dispatch *const dispatch, char **argv);
int								built_fg(t_dispatch *const dispatch, char **argv);
int								built_bg(t_dispatch *const dispatch, char **argv);
int								built_disown(t_dispatch *const dispatch, char **argv);
int								built_alias(t_dispatch *const dispatch, char **argv);
int								built_colors(t_dispatch *const dispatch, char **argv);
int								built_builtins(t_dispatch *const dispatch, char **argv);
int								built_kill(t_dispatch *const dispatch, char **argv);
int								built_envguard(t_dispatch *const dispatch, char **argv);

# define BUILTINS_COUNT 17
// exit + quit
typedef struct					s_load_builtins
{
	builtfunc					func;
	char						*id;
}								t_load_builtins;

typedef void					(*t_redfunc)(t_dispatch *const dispatch, int def);
// cmd //
void							red_r(t_dispatch *const dispatch, int def);
void							red_rr(t_dispatch *const dispatch, int def);
void							red_l(t_dispatch *const dispatch, int def);
void							red_ll(t_dispatch *const dispatch, int def);
void							red_lll(t_dispatch *const dispatch, int def);
void							red_ar(t_dispatch *const dispatch, int def);
void							red_la(t_dispatch *const dispatch, int def);
void							red_io(t_dispatch *const dispatch, int def);
// task //
void							tred_r(t_dispatch *const dispatch, int def);
void							tred_rr(t_dispatch *const dispatch, int def);
void							tred_l(t_dispatch *const dispatch, int def);
void							tred_ll(t_dispatch *const dispatch, int def);
void							tred_lll(t_dispatch *const dispatch, int def);
void							tred_ar(t_dispatch *const dispatch, int def);
void							tred_la(t_dispatch *const dispatch, int def);
void							tred_io(t_dispatch *const dispatch, int def);

typedef size_t 					(*perf_len)(t_dispatch *const dispatch, char **src);
typedef void 					*(*perf_push)(t_dispatch *const dispatch, char **src,
								char *dst);

size_t 							dollar_len(t_dispatch *const dispatch, char **src);
void 							*dollar_push(t_dispatch *const dispatch, char **src, 
								char *dst);
size_t 							escape_len(t_dispatch *const dispatch, char **src);
void 							*escape_push(t_dispatch *const dispatch, char **src,
								char *dst);
size_t 							home_len(t_dispatch *const dispatch, char **src);
void 							*home_push(t_dispatch *const dispatch, char **src,
								char *dst);

typedef struct 					s_perfom
{
	size_t 						index;
	perf_len 					func_len;
	perf_push 					func_push;
}								t_perfom;

typedef void 					(*exec_task)(t_dispatch *const dispatch, 
								t_task *const task);

typedef void 					(*t_execute)(t_dispatch *const dispatch, 
								t_task *const task, t_cmd *const cmd);

void 							exec_pure(t_dispatch *const dispatch, 
								t_task *const task, t_cmd *const cmd);

void 							exec_red(t_dispatch *const dispatch,
								t_task *const task, t_cmd *const cmd);

void 							exec_built(t_dispatch *const dispatch,
								t_task *const task, t_cmd *const cmd);

#endif
