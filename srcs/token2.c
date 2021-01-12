#include "../libft/libft.h"
#include "../includes/minishell.h"

void	ft_puttok_givflag(t_tok *tok, t_tok *firsttoken, char c)
{
	t_tok	*tmp;

	tmp = firsttoken;
	if (c == ' ')
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
	while (src[len] && src[len] != ' ' && flagstr[len] == '0')
		len++;
	if (!(dest = calloc(len, sizeof(char))))
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
		tmp->str[0] = ' ';
		tmp->str[1] = '\0';
	}
	return (0);
}

int     ft_get_tokens(t_mini *s, t_cmdl *cmd)
{
	int		i;

	i = 0;
	(void)s;
    ft_printf("On entre dans la fonction qui split les commandes en tokens.\n");
	while (cmd->str[i] == ' ')
		i++;
	while (cmd->str[i])
	{
		if (ft_add_token(cmd, i))
			return (ft_del_tokens(cmd, 1));
// inc i ' ' or quotes
		i = ft_inc_i(cmd->str, cmd->flag, i, cmd->flag[i]);
//		while (cmd->str[i] && cmd->str[i] != ' ')
//			i++;
//		if (cmd->str[i] && ft_add_token(cmd, i))
//			return (ft_del_tokens(cmd, 1));
//		while (cmd->str[i] && cmd->str[i] == ' ')
//			i++;
	}
	testtokkens(cmd);
    ft_printf("On quitte la fonction qui split les commandes en tokens.\n");
	return (ft_del_tokens(cmd, 0));
    return (0);
}