#include "../libft/libft.h"
#include "../includes/minishell.h"


void init_env(t_mini *s, char **env)
{
	int		i;
	/*t_env	new;*/

	i = 0;
	/*while (env[i] != NULL)*/
	/*{*/
		/*[>while (s->env->next != NULL)<]*/
			/*[>s->env->next = next;<]*/
		/*if (!(env = ft_calloc(sizeof(t_env), 1)))*/
			/*error(s, ERR_CALLOC);*/
		/*new.value = ft_strdup(env[i]);*/
		/*new.next = NULL;*/

		/*ft_printf("%d : %s\n", i, env[i]);*/
		/*i++;*/
	/*}*/
	/*s->env->value = 0;*/
	s->sig = 0;
	/*ft_printf("%d : %s\n", i, env[i]);*/
	ft_printf("%s\n", env[0]);
}

/*
** check if name variable contains only letters, numbers, underscores "_"
**and don't begin with numbers
*/

void	check_env_variable_name(t_mini *s)
{
	t_env	*env;
	int		i;

	env = s->env;
	while (env && env->next)
	{
		i = 0;
		while (env->name[i])
		{
			if (ft_isdigit(env->name[0]) == 1)
				error(s, ERR_INVALID_ENV_NAME);
			if (ft_isalnum(env->name[i]) == 0 && env->name[i] != '_')
				error(s, ERR_INVALID_ENV_NAME);
			i++;
		}
		env = env->next;
	}
}

/*
** split name and value into env->name and env->value, deleting the "=".
** if value is empty, replace by ""(empty string) and not NULL Char
*/

void	split_env_value(t_mini *s)
{
	t_env	*env;
	char	**tab;

	env = s->env;
	while (env)
	{
		tab = ft_split(env->value, '=');
		env->name = tab[0];
		env->value = tab[1];
		if (env->value == NULL)
			env->value = ft_strdup("");
		env = env->next;
	}
}

/*
**	copy every string of the env into s->env->value (linked list)
*/

void	copy_env(t_mini *s, char **env)
{
	int		i;
	t_env	*new;
	t_env	*old;

	i = 0;
	if (!(old = ft_calloc(sizeof(t_env), 1)))
		error(s, ERR_CALLOC);
	old->value = ft_strdup(env[i]);
	old->next = NULL;
	s->env = old;
	i++;
	while (env[i] && env)
	{
		if (!(new = ft_calloc(sizeof(t_env), 1)))
			error(s, ERR_CALLOC);
		new->value = ft_strdup(env[i]);
		new->next = NULL;
		old->next = new;
		old = new;
		i++;
	}
}

void	init_env(t_mini *s, char **env)
{
	copy_env(s, env);
	split_env_value(s);
	check_env_variable_name(s);

	/*t_env	*print;*/
	/*print = s->env;*/
	/*while (print)*/
	/*{*/
		/*ft_printf("-%s:", print->name);*/
		/*ft_printf("%s\n----\n", print->value);*/
		/*print = print->next;*/
	/*}*/
}
