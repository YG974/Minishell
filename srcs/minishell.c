#include "../libft/libft.h"
#include "../includes/minishell.h"

void init_mini(t_mini *s)
{
	s->std.in = STDIN;
	s->std.out = STDOUT;
	s->std.err = STDERR;
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
}
