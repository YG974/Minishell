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

/* FLAGS ON EVERY CHAR OF COMMAND LINE FOR THE PARSING */
# define S_QUOTED 1
# define D_QUOTED 2
# define ESCAPED 3

/* FLAGS FOR TOKENS */
# define FLAG_CMD 1
# define FLAG_SPACE 2
# define FLAG_LIT_CHAR 3
# define FLAG_STR 4
# define FLAG_ASSIGNEMENT 5

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
	void			*buf;
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
	int				pipe;
	int				redir;
	struct s_cmdl	*next;
}					t_cmdl;


typedef struct		s_mini
{
	struct s_env	*env;
	t_std			std;
	t_read			read;
	t_forparse		parse;
	t_cmdl			*firstcmdl;
	t_cmdl			*currentcmdl;
	char			**line;
	int				status;
	int				sig;
	int				error;
	int				i;
	struct s_mini			*next;
	struct s_mini			*previous;
}					t_mini;

/*
**	minishell.c
*/
void	init_mini(t_mini *s);
void	minishell(t_mini *s);
void	prompt(t_mini *s);

/*
**	env.c
*/
void	init_env(t_mini *s, char **env);
void	copy_env(t_mini *s, char **env);
void	check_env_validity(t_mini *s);
void	is_valid_env_name(t_mini *s, char *str);
char	*ft_strjoin_free_s1(char const *s1, char const *s2);

/*
**	ft_parse.c
*/
int     ft_check_semicolons(char *line);
int     ft_parse(t_mini *s);

/*
**	ft_get_cmd_lines.c
*/
int     ft_not_quoted(char *line, int i);
char    *ft_strdup_size(char *line, int end, int start);
t_cmdl    *ft_create_cmdl(t_mini *s);
int     ft_del_cmdline(t_mini *s, int ret);
int     ft_get_cmd(char *line, t_mini *s);

/*
**	ft_init_signal.c
*/
int     init_signal(t_mini *s);

/*
**	ft_redirection.c
*/
int     ft_redirection(t_mini *s);

/*
**	ft_exe_cmd.c
*/
void	ft_exe_cmd(t_mini *s, t_cmdl *cmd);
void	print_tab(char **tab);
char	**put_env_in_tab(t_mini *s);

/*
**	ft_error.c
*/
void	error(t_mini *s, int error);

/*
**	token.c
*/
void	break_cmdline_into_token(t_mini *s);
int		is_char_set(int c, const char *char_set);

/*
**	token2.c
*/
int     ft_get_tokens(t_mini *s, t_cmdl *cmd);
int		ft_add_token(t_cmdl *cmd, int i);
int		ft_del_tokens(t_cmdl *cmd, int ret);
char	*ft_strdup_meta(char *src, char *flagstr);
void	ft_puttok_givflag(t_tok *tok, t_tok *firsttoken, char c);
void	testtokkens(t_cmdl *cmd);//function to del

/*
**	token3.c
*/
int		ft_lit_char(t_cmdl *cmd, int i);
char	*ft_strdup_quotes(char *src, char *flagstr, char c);
int		ft_inc_i(char *str, char *flag, int i, char c);
int		ft_ismeta(char c);



#endif

/*
**	if quotes are not even -> error
**	if ";;" error 
**	operator or word
**	boolean to know if quoted, control operator, redir etc
**	delete space tab etc
**	
*/


    //ft_printf("===========> On est rentré dans la fonction de PARSING <============\n");
