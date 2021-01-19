#include "../includes/minishell.h"

/*
** check if name variable contains only letters, numbers, underscores "_"
**and don't begin with numbers
*/
#include "../libft/libft.h"

char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	if (!(s2 && s1))
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[len1 + len2] = '\0';
	free((void *)s1);
	return (str);
}

char **put_env_in_tab(t_mini *s)
{
	t_env	*env;
	char	*env_str;
	char	**env_tab;

	env = s->env;
	env_str = strdup("");
	while (env)
	{
		env_str = ft_strjoin_free_s1(env_str, env->name);
		env_str = ft_strjoin_free_s1(env_str, "=");
		env_str = ft_strjoin_free_s1(env_str, env->value);
		env_str = ft_strjoin_free_s1(env_str, "\n");
		env = env->next;
	}
		/*printf("%s\n", env_str);*/
	env_tab = ft_split(env_str, '\n');
	free(env_str);
	return (env_tab);
}

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
