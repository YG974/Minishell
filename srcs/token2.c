#include "../libft/libft.h"
#include "../includes/minishell.h"

void	ft_puttok_givflag(t_tok *tok, t_tok *firsttoken, char c)
{
	t_tok	*tmp;

	tmp = firsttoken;
	if (ft_ismeta(c))
		tok->flag = FLAG_SPACE;
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
		return(ft_strdup_quotes(src, flagstr, flagstr[i]));
	while (src[len] && !ft_ismeta(src[len]) && flagstr[len] == '0')
		len++;
	if (!(dest = calloc(len + 1, sizeof(char))))
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

void	testtokkens(t_cmdl *cmd)
{
	int i;

	i = 1;
	cmd->token = cmd->firsttoken;
	while (cmd->token)
	{
		ft_printf("TEST TOKEN #%d : %s\n", i, cmd->token->str);
		i++;
		cmd->token = cmd->token->next;
	}
	ft_printf("Fin des tokens\n\n");
}

int		ft_add_token(t_cmdl *cmd, int i)
{
	t_tok *tmp;

	if (!(tmp = calloc(1, sizeof(t_tok))))
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
		if (!(tmp->str = calloc(2, sizeof(char))))
			return (1);
		tmp->str[0] = cmd->str[i];
		tmp->str[1] = '\0';
	}
	return (0);
}

int     ft_get_tokens(t_mini *s, t_cmdl *cmd)
{
	int		i;

	i = 0;
	(void)s;
    // ft_printf("On entre dans la fonction qui split les commandes en tokens.\n");
	while (cmd->str[i] == ' ')
		i++;
	while (cmd->str[i])
	{
		if (cmd->str[i] == '\\')
		{
			if (ft_lit_char(cmd, i))
				return (ft_del_tokens(cmd, 1));
			i += 2;
		} else
		{
			if (ft_add_token(cmd, i))
				return (ft_del_tokens(cmd, 1));
			i = ft_inc_i(cmd->str, cmd->flag, i, cmd->flag[i]);
		}
	}
	//testtokkens(cmd);
    // ft_printf("On quitte la fonction qui split les commandes en tokens.\n");
	return (0);
}