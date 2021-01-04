#include "../libft/libft.h"
#include "../includes/minishell.h"

/*
**	copy every string of the env in s->env linked list
*/

void init_env(t_mini *s, char **env)
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
	while (env[i] != NULL)
	{
		if (!(new = ft_calloc(sizeof(t_env), 1)))
			error(s, ERR_CALLOC);
		new->value = ft_strdup(env[i]);
		new->next = NULL;
		old->next = new;
		old = new;
		/*ft_printf("%d : %s\n", i, env[i]);*/
		i++;
	}

	while (s->env->next)
	{
		ft_printf("%s\n", s->env->value);
		s->env = s->env->next;
	}
}

