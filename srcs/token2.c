/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:21:23 by pcoureau          #+#    #+#             */
/*   Updated: 2021/02/10 12:21:37 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_wich_meta(char c)
{
	if (c == '>' || c == '<' || c == ' ')
		return (FLAG_SPACE);
	return (FLAG_PIPE);
}

void	ft_puttok_givflag(t_tok *tok, t_tok *firsttoken, char c)
{
	t_tok	*tmp;

	tmp = firsttoken;
	if (ft_ismeta(c))
		tok->flag = ft_wich_meta(c);
	else
		tok->flag = FLAG_STR;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tok;
	tok->prev = tmp;
	tok->next = NULL;
}

char	*ft_strdup_meta(char *src, char *flagstr)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = 0;
	if (flagstr[i] == '1' || flagstr[i] == '2')
		return (ft_strdup_quotes(src, flagstr, flagstr[i]));
	while (src[len] && !ft_ismeta(src[len]) && flagstr[len] == '0')
		len++;
	if (!(dest = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_del_tokens(t_cmdl *cmd, int ret)
{
	t_tok	*tmp;
	t_tok	*todel;

	todel = cmd->firsttoken;
	while (todel->prev)
		todel = todel->prev;
	while (todel)
	{
		tmp = todel->next;
		if (todel->str)
			free(todel->str);
		free(todel);
		todel->str = NULL;
		todel->next = NULL;
		todel = tmp;
	}
	cmd->firsttoken = NULL;
	return (ret);
}

int		ft_add_token(t_cmdl *cmd, int i)
{
	t_tok *tmp;

	if (!(tmp = ft_calloc(1, sizeof(t_tok))))
		return (1);
	if (!cmd->firsttoken)
	{
		tmp->flag = FLAG_CMD;
		cmd->firsttoken = tmp;
		if (ft_ismeta(cmd->str[i]))
			tmp->flag = FLAG_SPACE;
	}
	else
		ft_puttok_givflag(tmp, cmd->firsttoken, cmd->str[i]);
	if (tmp->flag != FLAG_SPACE)
	{
		if (!(tmp->str = ft_strdup_meta(cmd->str + i, cmd->flag + i)))
			return (1);
	}
	else
	{
		if (!(tmp->str = ft_calloc(2, sizeof(char))))
			return (1);
		tmp->str[0] = cmd->str[i];
	}
	return (0);
}
