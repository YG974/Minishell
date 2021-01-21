#include "../libft/libft.h"
#include "../includes/minishell.h"
int		echo_flag_on(char *str)
{
	int i;

	i = 2;
	/*ft_printf("str echo %s\n", str);*/
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

int		ft_echo(t_mini *s, char **args)
{
	int		n_flag;
	int		i;

	n_flag = 0;
	i = 1;
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
	if (n_flag == 0)
		ft_putstr_fd("\n", s->std.out);
	ft_printf("flag %d\n", n_flag);
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
	(void)s;
	(void)args;
	ft_printf("env \n");
	return (0);
}

int		ft_exit(t_mini *s, char **args)
{
	(void)s;
	(void)args;
	ft_printf("exit \n");
	return (WANT_EXIT);
}
