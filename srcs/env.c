#include "../libft/libft.h"
#include "../includes/minishell.h"


void init_env(t_mini *s, char **env)
{
	/*int		i;*/
	/*t_env	new;*/

	/*i = 0;*/
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
	env[0] = 0;
	s->env->value = 0;
}

