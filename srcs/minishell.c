#include "../libft/libft.h"
#include "../includes/minishell.h"

void prompt(t_mini *s)
{	
	ft_printf("MINISHELL DU TURFU ---> ");
	s->read.ret = read(s->read.fd, s->read.buf, s->read.count);
}

void init_mini(t_mini *s)
{
	s->std.in = STDIN;
	s->std.out = STDOUT;
	s->std.err = STDERR;
	s->read.ret = 0;
	s->read.count = 0;
	s->read.fd = 0;
	s->read.buf = NULL;
	s->sig = 0;
	s->status = 0;
	s->next = NULL;
	s->previous = NULL;
	s->first_token = NULL;
	s->current_token = NULL;
	s->previous_token = NULL;
	s->read.fd = STDIN;
	s->read.count = BUFF_SIZE;
}

void	minishell(t_mini *s)
{
	init_signal(s);
	while(!s->status)
	{
		if (!(s->read.buf = ft_calloc(BUFF_SIZE, sizeof(char))))
			error(s, ERR_CALLOC);
		prompt(s);
		if (!s->status && ft_parse(s))
			error(s, ERR_CALLOC);
		if (!s->status && ft_redirection(s))
			error(s, ERR_CALLOC);
		if (!s->status && ft_exe_cmd(s))
			error(s, ERR_CALLOC);
		free(s->read.buf);
	}
}

int		main(int ac, char **av, char **env)
{
	t_mini	s;

	(void)ac;
	(void)av;
	int a;
	init_mini(&s);
a =	write(1, "\n", 1);
	init_env(&s, env);
	s.sig = ft_printf("Yann a des gros hemorroides a cause de ses frequentations douteuses.\n");
	minishell(&s);
	ft_printf("END OF MINISHELL\n");
	return (0);
}
