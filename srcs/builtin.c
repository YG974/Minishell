#include "../libft/libft.h"
#include "../includes/minishell.h"

int		echo_flag_on(char *str)
{
	int i;

	i = 2;
	if (str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int		count_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int		ft_echo(t_mini *s, char **args)
{
	int		n_flag;
	int		i;
	int		nb;

	n_flag = 0;
	i = 1;
	if ((nb = count_args(args)) > 1)
	{
		while (echo_flag_on(args[i]) && args[i])
		{
			n_flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], s->std.out);
			i++;
			if (args[i])
				ft_putstr_fd(" ", s->std.out);
		}
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", s->std.out);
	return (0);
}

int		ft_cd(t_mini *s, char **args)
{
	(void)s;
	(void)args;
	ft_printf("cd \n");
	return (0);
}

int		ft_pwd(t_mini *s, char **args)
{
	(void)s;
	(void)args;
	ft_printf("pwd \n");
	return (0);
}

int		ft_export(t_mini *s, char **args)
{
	(void)s;
	(void)args;
	ft_printf("export \n");
	return (0);
}

int		ft_unset(t_mini *s, char **args)
{
	(void)s;
	(void)args;
	ft_printf("unset \n");
	return (0);
}

int		ft_env(t_mini *s, char **args)
{
	int		i;
	t_env	*env;

	env = s->env;
	if ((i = count_args(args)) > 1)
	{
		ft_putstr_fd("Error: flag or argument forbidden with env command .\n",
				s->std.err);
		return (1);
	}
	while (env)
	{
		ft_putstr_fd(env->name, s->std.out);
		ft_putstr_fd("=", s->std.out);
		ft_putstr_fd(env->value, s->std.out);
		ft_putstr_fd("\n", s->std.out);
		env = env->next;
	}
	return (0);
}

int		str_is_digit(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+' )
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
// si on veut peaufiner, bien checker a verifier si un seul argument, et que 
// cest un nombre, dans ce cas, return ce nombre, sinon renvoyer de dernier
// retour cmd->ret
// Dans le sujet c'est ecrit, sans option, mais pas sans argument.
int		ft_exit(t_mini *s, char **args)
{
	(void)s;
	int		i;

	i = count_args(args);
	if (i > 2)
	{
		ft_printf("Error: exit command allows only an numeric argument.\n");
		ft_printf("Ex : exit 4\n");
		return (1);
	}
	if (!(i = str_is_digit(args[1])))
	{
		ft_printf("Error: exit command allows only an numeric argument.\n");
		ft_printf("Ex : exit 4\n");
		return (1);
	}
	return (0);
}
