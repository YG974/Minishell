#include "../libft/libft.h"
#include "../includes/minishell.h"

void prompt(t_mini *s)
{	
	/*ft_printf("MINISHELL DU TURFU ---> ");*/
	ft_putstr_fd("MINISHELL DU TURFU ---> ", 1);
	/*get_next_line(0, s->read.buf);*/
	s->read.ret = read(s->read.fd, s->read.buf, s->read.count);
	if (s->read.ret == 0)
		s->error = 2;
		/*ft_putstr_fd("\n", 2);*/

		/*minishell(s);*/
		/*ft_putstr_fd("\nMINISHELL DU TURFU ---> ", 1);*/
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
	s->status = 0;
	s->read.fd = STDIN;
	s->read.count = BUFF_SIZE;
	s->parse.semcol = 0;
	s->firstcmdl = NULL;
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while(env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	minishell(t_mini *s)
{
	while(!s->status && s->error != 2)
	{
		if (!(s->read.buf = ft_calloc(BUFF_SIZE, sizeof(char))))
			error(s, ERR_CALLOC);
		init_signal(s);
		prompt(s);
		/*if (ft_parse(s))*/
		if (!s->status && s->error != 2 && ft_parse(s))
			error(s, ERR_CALLOC);
		free(s->read.buf);
	}
	ft_free_env(s->env);
	s->env = NULL;
}

int		main(int ac, char **av, char **env)
{
	t_mini	s;

	(void)ac;
	(void)av;

	init_mini(&s);
	init_env(&s, env);
	minishell(&s);
	ft_printf("END OF MINISHELL\n");
	return (0);
}
