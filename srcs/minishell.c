/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:19:44 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 10:49:32 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

void	prompt(t_mini *s)
{
	while (1)
	{
		ft_putstr_fd(CYAN, STDOUT);
		ft_putstr_fd("MINISHELL DU TURFU -> ", STDOUT);
		ft_putstr_fd(RESET, STDOUT);
		s->read.ret = read(s->read.fd, s->read.buf, s->read.count);
		if (s->read.ret)
		{
			while (s->read.buf[s->read.ret - 1] != '\n')
			{
				ft_putstr_fd("  \b\b", 1);
				s->read.ret += read(s->read.fd, &s->read.buf[s->read.ret],
						s->read.count);
			}
			s->read.buf[s->read.ret] = '\n';
		}
		else
		{
			ft_putstr_fd("  \b\bexit\n", 1);
			s->error = 2;
			return ;
		}
		return ;
	}
}

void	init_mini(t_mini *s)
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
	s->read.fd = STDIN;
	s->read.count = BUFF_SIZE;
	s->parse.semcol = 0;
	s->firstcmdl = NULL;
	s->firstfd = 0;
	s->std.sin = dup(STDIN);
	s->std.out = dup(STDOUT);
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
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
	while (!s->status && s->error != 2)
	{
		if (!(s->read.buf = ft_calloc(BUFF_SIZE, sizeof(char))))
			error(s, ERR_CALLOC);
		init_signal(s);
		prompt(s);
		if (!s->status && s->error != 2 && ft_parse(s))
			;
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
	close(0);
	close(1);
	close(2);
	ft_printf("END OF MINISHELL\n");
	return (g_sig.ret);
}
