#include "../libft/libft.h"
#include "../includes/minishell.h"

/*
**      FONCTIONS SUREMENT UTILES PLUS TARD
**      A GARDER DE COTE, ET SI ON S'EN SERT PAS BAH IL FAUT SUPPRIMER LE FICHIER DUH

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
*/