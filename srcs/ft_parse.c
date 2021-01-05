#include "../libft/libft.h"
#include "../includes/minishell.h"

int     ft_check_semicolons(char *line)
{
    int     i;

    i = 0;
    while (line[i])
    {
        if (i > 0 && line[i - 1] == '\\')
            i = i + 0;
        else if (line[i] == ';' && !ft_not_quoted(line, i))
        {
            i++;
            while (line[i] != '\0' && line[i] == ' ')
                i++;
            if (line[i] == ';')
                return (1);
        }
        else
            i++;
    }
    return (0);
}

int     ft_parse(t_mini *s)
{
    int     ret;

    ret = 0;
    ft_printf("===========> On est rentré dans la fonction de PARSING <============\n");
    if (ft_check_semicolons(s->read.buf))
        error(s, ERR_SEMCOL);
    /*if (!s->error && (ret = ft_get_cmd(s->read.buf, s)))
        error(s, ret);*/
    ft_printf("===========> On sort de la fonction de PARSING <============\n");
    return (0);
}