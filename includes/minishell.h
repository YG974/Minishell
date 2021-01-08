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
# define ERR_PARSING 11
# define ERR_QUOTES 12
# define ERR_TOKEN 13
# define ERR_META 14
# define ERR_SEMCOL 15
# define ERR_GETCMD 16

/* FLAGS ON EVERY CHAR OF COMMAND LINE FOR THE PARSING */
# define S_QUOTED 1
# define D_QUOTED 2
# define ESCAPED 3



typedef struct		s_tok
{
	char			*line;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_env
{
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
	char			*line;
	struct s_cmdl	*next;
}					t_cmdl;


typedef struct		s_mini
{
	struct s_env	*env;
	t_std			std;
	t_read			read;
	t_forparse		parse;
	t_tok			*first_token;
	t_tok			*current_token;
	t_tok			*previous_token;
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

void init_mini(t_mini *s);

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

/*
**	ft_parse.c
*/
int     ft_check_semicolons(char *line);
int     ft_parse(t_mini *s);

/*
**	ft_get_cmd_lines.c
*/
int     ft_not_quoted(char *line, int i);
char    *ft_strdup_size(char *line, int i, int j);
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
int     ft_exe_cmd(t_mini *s);

/*
**	ft_error.c
*/
void	error(t_mini *s, int error);

/*
**	token.c
*/
void break_cmdline_into_token(t_mini *s);
int is_char_set(int c, const char *char_set);
#endif

    //ft_printf("===========> On est rentré dans la fonction de PARSING <============\n");
