/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:07:14 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:33:23 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define BUFF_SIZE 4096

# define ERR_CALLOC 1
# define ERR_INVALID_ENV_NAME 2
# define ERR_PARSING 11
# define ERR_QUOTES 12
# define ERR_TOKEN 13
# define ERR_META 14
# define ERR_SEMCOL 15
# define ERR_GETCMD 16
# define ERR_EXEC_CMD 17
# define WANT_EXIT 18

/*
**	FLAGS ON EVERY CHAR OF COMMAND LINE FOR THE PARSING
*/
# define S_QUOTED 1
# define D_QUOTED 2
# define ESCAPED 3
# define TO_EXPAND 4
# define BLANK 5
# define META 6
# define WORD 7

/*
**	FLAGS FOR TOKENS
*/
# define FLAG_CMD 1
# define FLAG_SPACE 2
# define FLAG_LIT_CHAR 3
# define FLAG_STR 4
# define FLAG_ASSIGNEMENT 5
# define FLAG_PIPE 6
# define S_GREATER 11
# define D_GREATER 12
# define S_LESS 13
# define S_PIPE 14
# define S_SEMICOLON 15
# define D_PIPE 16
# define D_LESS 17
# define D_SEMICOLON 18

# define NOT_EXEC 126
# define CMD_NOT_FOUND 127

/*
**	COLOR
*/
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"
# define RED "\x1b[31m"

typedef struct		s_tok
{
	char			*str;
	int				flag;
	struct s_tok	*prev;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_read
{
	ssize_t			ret;
	size_t			count;
	char			*buf;
	int				fd;
}					t_read;

typedef struct		s_std
{
	int				in;
	int				out;
	int				err;
}					t_std;

typedef	struct		s_forparse
{
	int				semcol;
}					t_forparse;

typedef	struct		s_cmdl
{
	t_tok			*firsttoken;
	t_tok			*token;
	char			*str;
	char			*flag;
	char			*buf;
	int				ret;
	struct s_cmdl	*next;
}					t_cmdl;

typedef	struct		s_parse
{
	char			*str;
	char			*flag;
	char			*buf;
}					t_parse;

typedef	struct		s_sig
{
	int				interrupt;
	int				quit;
	int				status;
	int				ret;
	pid_t			pid;
}					t_sig;

typedef struct		s_mini
{
	struct s_env	*env;
	t_std			std;
	t_std			pipe;
	t_read			read;
	t_forparse		parse;
	t_cmdl			*firstcmdl;
	t_cmdl			*currentcmdl;
	t_parse			p;
	char			**line;
	int				status;
	int				parsed;
	int				sig;
	int				error;
	int				i;
	int				j;
	int				firstfd;
}					t_mini;

t_sig	g_sig;

/*
**	minishell.c
*/
void				init_mini(t_mini *s);
void				ft_free_env(t_env *env);
void				minishell(t_mini *s);
void				prompt(t_mini *s);

/*
**	builtin.c
*/
int					echo_flag_on(char *str);
int					count_args(char **args);
int					ft_echo(t_mini *s, char **args);
int					go_to_path(t_mini *s, char *args);
int					go_to_home_path(t_mini *s);

/*
**	builtin2.c
*/
int					ft_cd(t_mini *s, char **args);
int					ft_pwd(t_mini *s, char **args);
int					is_valid_env_name(char *str);
int					print_sorted_env(t_mini *s);
int					ft_strchr_int(const char *s, int c);

/*
**	builtin3.c
*/
int					is_in_env(t_mini *s, char *str);
char				*get_name(char *str);
void				ct_export_value(t_mini *s, char *name, char *str, int pos);
void				md_export_value(t_mini *s, char *name, char *str, int pos);
void				export_assignement(t_mini *s, char *str);

/*
**	builtin4.c
*/
int					ft_export(t_mini *s, char **args);
void				unset_value(t_mini *s, char *args);
int					ft_unset(t_mini *s, char **args);
int					ft_env(t_mini *s, char **args);
int					str_is_digit(char *str);

/*
**	builtin5.c
*/
int					ft_exit(t_mini *s, char **args);
char				**put_sorted_env_in_tab(t_mini *s);
char				**sort_tab_env(char **s_env);
int					print_sorted_env(t_mini *s);
void				cd_str_error(char *s1, int flag);

/*
**	env.c
*/
char				*ft_strjoin_free_s2(char const *s1, char const *s2);
char				*ft_strjoin_free_s1(char const *s1, char const *s2);
char				**put_env_in_tab(t_mini *s);
void				check_env_variable_name(t_mini *s);
void				split_env_value(t_mini *s);

/*
**	env2.c
*/
void				copy_env(t_mini *s, char **env);
void				init_env(t_mini *s, char **env);

/*
**	what is this function ?
*/
void				check_env_validity(t_mini *s);

/*
**	ft_parse.c
*/
int					ft_check_semicolons(char *line);
int					ft_parse(t_mini *s);

/*
**	ft_get_cmd_lines.c
*/
int					ft_not_quoted(char *line, int i);
char				*ft_strdup_size(char *line, int end, int start);
t_cmdl				*ft_create_cmdl(t_mini *s);
int					ft_del_cmdline(t_mini *s, int ret);
int					ft_get_cmd(char *line, t_mini *s);

/*
**	ft_init_signal.c
*/
int					init_signal(t_mini *s);

/*
**	ft_redirection.c
*/
int					ft_redirection(t_mini *s, t_cmdl *cmd);

/*
**	ft_pipes.c
*/
int					thereisapipe(t_cmdl *cmd);
int					ft_firstpipe(t_mini *s, t_cmdl *cmd);
int					ft_pipe(t_mini *s, t_cmdl *cmd);

/*
**	ft_exe_cmd.c
*/
void				ft_exe_cmd(t_mini *s, t_cmdl *cmd);
void				print_tab(char **tab);
char				**put_env_in_tab(t_mini *s);

/*
**	ft_exe_cmd.c
*/
int					ft_echo(t_mini *s, char **args);
int					ft_cd(t_mini *s, char **args);
int					ft_pwd(t_mini *s, char **args);
int					ft_export(t_mini *s, char **args);
int					ft_unset(t_mini *s, char **args);
int					ft_env(t_mini *s, char **args);
int					ft_exit(t_mini *s, char **args);
void				handle_dollar_question_mark(t_mini *s, t_cmdl *cmd);
void				ft_free_tab(char **env);

/*
**	search_bin.c
*/
char				*try_bin_path(char *bin_path, char *cmd_name);
int					check_bin_right(char *path, char **args);
char				*find_bin_path(t_mini *s, char **args);
int					exec_bin(t_mini *s, t_cmdl *cmd, char **args);
int					ft_str_error(char *path, char *str, int ret);

/*
**	parse_cmd_args.c
*/
t_cmdl				*join_tokens(t_cmdl *cmd);
int					parse_cmd_args(t_mini *s, t_cmdl *cmd);
t_tok				*norme_chlag(t_tok *token);
void				parse_cmd_args2(t_cmdl *cmd);
t_cmdl				*join_tokens(t_cmdl *cmd);

/*
**	exec_tools.c
*/
int					apply_assignement(t_mini *s, t_cmdl *cmd);
int					cmd_has_only_assignement(t_cmdl *cmd);
void				ft_free_tab(char **env);
void				closepipes(t_mini *s);

/*
**	ft_error.c
*/
void				error_fd(char *s);
void				error(t_mini *s, int error);

/*
**	token.c
*/
char				*get_env_value(t_mini *s, char *name);

/*
**	token2.c
*/
int					ft_wich_meta(char c);
void				ft_puttok_givflag(t_tok *tok, t_tok *firsttoken, char c);
char				*ft_strdup_meta(char *src, char *flagstr);
int					ft_del_tokens(t_cmdl *cmd, int ret);
int					ft_add_token(t_cmdl *cmd, int i);

/*
**	token3.c
*/
char				*ft_without_quotes(char *s, int i, int j);
char				*ft_strdup_quotes(char *src, char *flagstr, char c);
int					paco_mange_tes_morts(char *str, int i);
int					extreme(char *str, int i);
int					ft_inc_i(char *str, char *flag, int i, char c);

/*
**	token4.c
*/
void				ft_closefd(t_mini *s);
int					break_cmdline_into_token(t_mini *s);
void				free_cmd_str(t_cmdl *cmd);

/*
**	token5.c
*/
int					is_char_set(int c, const char *char_set);
int					ft_get_tokens(t_mini *s, t_cmdl *cmd);
int					ft_ismeta(char c);
int					ft_lit_char(t_cmdl *cmd, int i);

/*
**	ft_split_ms.c
*/
char				**ft_split_ms(char const *s, char c);

#endif
#ifndef SIZE_T_MAX
# define SIZE_T_MAX 10000
#endif
