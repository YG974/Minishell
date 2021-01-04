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

typedef struct		s_mini
{
	struct s_env	env;
	t_std			std;
	t_read			read;
	int				status;
	int				sig;
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
void init_env(t_mini *s, char **env);

/*
**	ft_parse.c
*/
int     ft_parse(t_mini *s);

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

#endif
