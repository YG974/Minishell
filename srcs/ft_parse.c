#include "../libft/libft.h"
#include "../includes/minishell.h"

int     ft_parse(t_mini *s)
{
    int     ret;

    ret = 0;
    ft_printf("===========> On est rentré dans la fonction de PARSING <============\n");
    if ((ret = ft_get_cmd(s->read.buf, s)))
        error(s, ret);
    ft_printf("===========> On sort de la fonction de PARSING <============\n");
    return (0);
}