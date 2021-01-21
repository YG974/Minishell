#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_echo(t_mini *s, char **args)
{
	int		n_flag;
	int		i;

	n_flag = 0;
	i = 1;
	while (args[i])
	{
		if (ft_strncmp("-n", args[i], 2))
		{
			n_flag = 1;
			i++;
		}
		else
			ft_putstr_fd(args[i], s->std.out);
		if (args[i + 1])
			ft_putstr_fd(" ", s->std.out);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", s->std.out);
	ft_printf("echo \n");
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
