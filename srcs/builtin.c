#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <sys/syslimits.h>

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

int		go_to_path(t_mini *s, char **args)
{
	(void)s;
	int		i;

	i = chdir(args[1]);
	if (i != 0)
		ft_putstr_fd("Error, couldn't change dir", 2);
	return (i);
}

int		go_to_home_path(t_mini *s)
{
	char	*path;
	int		i;

	path = ft_strdup("HOME");
	path = get_env_value(s, path);
	if ((i = ft_strlen(path)) < 1)
	{
		ft_putstr_fd("HOME is not defined\n", 2);
		return (1);
	}
	i = chdir(path);
	if (i != 0)
		ft_putstr_fd("Error, couldn't change dir", 2);
	ft_printf("home path %s", path);
	return (i);
}

int		ft_cd(t_mini *s, char **args)
{
	(void)s;
	int		i;

	i = count_args(args);
	if (i == 1)
		return (go_to_home_path(s));
	else
		return (go_to_path(s, args));
	ft_printf("cd \n");
	/*ft_putstr_fd("Error: cd command allows only one argument.\n", 2);*/
}

int		ft_pwd(t_mini *s, char **args)
{
	(void)s;
	char *cwd;

	cwd = ft_calloc(PATH_MAX, sizeof(char));
	if (!cwd)
	{
		error(s, ERR_CALLOC);
		return (1);
	}
	cwd = getcwd(args[1], PATH_MAX);
	if (!cwd)
	{
		ft_putstr_fd("Error, couldn't get current dir", 2);
		return (1);
	}
	ft_putstr_fd(cwd, s->std.out);
	ft_putstr_fd("\n", s->std.out);
	/*ft_printf("pwd \n");*/
	return (0);
}

int		is_valid_env_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[0]) == 1)
			return (0);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	/*ft_printf("export \n");*/
	return (1);
}

int		print_sorted_env(t_mini *s)
{
	t_env	*env;

	env = s->env;
	ft_printf("sorted env\n");
	return (0);

}

int		ft_strchr_int(const char *s, int c)
{
	int i;

	i = 0;
	c = (char)c;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

int		is_in_env(t_mini *s, char *str)
{
	t_env	*env;
	int		len;

	env = s->env;
	len = ft_strlen(str);
	while (env)
	{
		if (ft_strncmp(env->name, str, len) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	export_assignement(t_mini *s, char *str)
{
	t_env	*env;
	t_env	*new;
	char	*tmp;
	int		pos;

	env = s->env;
	if (is_in_env(s, str) == 0)
		if (!(new = ft_calloc(1, sizeof(t_env))))
			return error(s, ERR_CALLOC);
	pos = ft_strchr_int(str, '=');
	if (pos < 0)
		tmp = ft_strdup(str);
	else
	{
		tmp = ft_strdup_size(str, pos - 1, 0);
		new->name = tmp;
		if (str[pos + 1])
		{
			tmp = ft_strdup_size(str, ft_strlen(str), pos + 1);
			new->value = tmp;
		}
	}
	ft_printf("apply %s\n", str);
}

int		ft_export(t_mini *s, char **args)
{
	int		i;
	int		ret;

	i = 1;
	if ((ret = count_args(args)) == 1)
		return (print_sorted_env(s));
	while (args[i])
	{
		if (!(ret = is_valid_env_name(args[i])))
			error(s, ERR_INVALID_ENV_NAME);
		else
			export_assignement(s, args[i]);
		i++;
	}
	ft_printf("export \n");
	/*ft_printf("export \n");*/
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
		if (env->value)
		{
		ft_putstr_fd(env->name, s->std.out);
		ft_putstr_fd("=", s->std.out);
		ft_putstr_fd(env->value, s->std.out);
		ft_putstr_fd("\n", s->std.out);
		}
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
