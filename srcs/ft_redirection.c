#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_change_fd(t_mini *s, t_tok *tok)
{
	t_tok	*tmp;

	tmp = tok->next;
	while (tmp && tmp->flag != FLAG_STR)
		tmp = tmp->next;
	if (!tmp)
		return (1);
	if (tok->str[0] == '>')
	{
		if(tok->next->str[0] == '>')
		{
			if (s->std.out > 1)
				close(s->std.out);
			s->std.out = open(tmp->str, O_WRONLY | O_CREAT | O_APPEND, 00644);
			tok = tok->next;
			dup2(s->std.out, 1);
		}
		else
		{
			if (s->std.out > 1)
				close(s->std.out);
			s->std.out = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 00644);
			dup2(s->std.out, 1);
		}
	}
	if (tok->str[0] == '<')
	{
		if (s->std.in > 0)
			close(s->std.in);
		s->std.in = open(tmp->str, O_RDONLY);
		dup2(s->std.in, 0);
	}
	return (0);
}

int     ft_redirection(t_mini *s, t_cmdl *cmd)
{
    t_tok   *tmp;

    tmp = cmd->firsttoken;
    //printf("%d\n%d\n", s->std.in, s->std.out);
    //checker si il y a un < ou >. Si oui, il faut changer stdin et/ou stdout.
    while (tmp)
    {
        if (tmp->str[0] == '>' || tmp->str[0] == '<' || tmp->str[0] == '|')
            if (ft_change_fd(s, tmp))
				return (1);
		if (tmp->str[0] == '>' && tmp->next && tmp->next->str[0] == '>')
			tmp = tmp->next->next;
        tmp = tmp->next;
    }
    return(0);
}