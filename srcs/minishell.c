#include "../libft/libft.h"
#include "../includes/minishell.h"

void error(t_mini *s, int error)
{
	int	ret;

	s->status = 0;
	if (error == ERR_CALLOC)
		ret = ft_printf("Memory Allocation fail");
}

void prompt(t_mini *s)
{
	s->read.fd = STDIN;
	s->read.count = BUFF_SIZE;
	if (!(s->read.buf = ft_calloc(BUFF_SIZE, sizeof(char))))
		error(s, ERR_CALLOC);
	while(1)
	{
		ft_printf("MINISHELL DU TURFU ---> ");
		s->read.ret = read(s->read.fd, s->read.buf, s->read.count);
		/*ft_printf("%s", s->read.buf);*/
	}
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
}

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	
	t_mini	s;
	init_mini(&s);
	s.sig = ft_printf("paco c'est un GROS GAYYYYYY hihihi\n\n");
	prompt(&s);
	return (0);
}
