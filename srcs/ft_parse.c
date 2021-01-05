#include "../libft/libft.h"
#include "../includes/minishell.h"

int     ft_check_quotes(char *line)
{
    int i;
    int q;

    i = 0;
    q = 0;
    while (line[i])
    {
        if (i > 0 && line[i - 1] == '\\')
            q = q + 0;
        else if (line[i] == '\'' && q == 0)
            q = 1;
        else if (line[i] == '\"' && q == 0)
            q = 2;
        else if (line[i] == '\'' && q == 1)
            q = 0;
        else if (line[i] == '\"' && q == 2)
            q = 0;
        i++;
    }
    return (q);
}

int     ft_get_meta(char *line, t_mini *s)
{
    int i;
    int count;

    i = 0;
    count = 0;
    (void)s;
    while (line[i])
    {
        if (i > 0 && line[i - 1] == '\\')
            count = count + 0;
        else if (line[i] == '|' || line[i] == ';' || line[i] == '<' || line[i] == '>')
            if (!ft_check_quotes(line + i))
                count++;
        i++;
    }
    ft_printf("metacharacters (except spaces) : %d\n", count);
    return (0);
}

int     ft_get_tokens(char *line, t_mini *s)
{
    int i;

    i = 0;
    (void)s;
    while (line[i])
    {
        i++;
    }
    return (0);
}

/*
**  line is on s->read.buf
*/
int     ft_parse(t_mini *s)
{
    (void)s;
    ft_printf("===========> On est rentré dans la fonction de PARSING <============\n");
    //checking quotes
    if (ft_check_quotes(s->read.buf))
        error(s, ERR_QUOTES);
    //get metacharacters `|` , `&`, `;`, `(`, `)`, `<`, or `>`.
    ft_printf("\nSTATUS %d\n", s->status);
    if (!s->status && ft_get_meta(s->read.buf, s))
        error(s, ERR_META);
    //get token by token in chainlist
    if (!s->status && ft_get_tokens(s->read.buf, s))
        error(s, ERR_TOKEN);
    ft_printf("===========> On sort de la fonction de PARSING <============\n");
    return(0);
}