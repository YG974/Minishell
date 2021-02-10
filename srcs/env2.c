/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:17:16 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:17:18 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

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
}
