#include "../libft/libft.h"
#include "../includes/minishell.h"

/*
 ** s->line[0] = command line;
 * s->line[1] = flags or comments;
 * s->line[0][i] = char i of the line;
 * s->line[1][i] = flags or comments on char i;
 */

void break_cmdline_into_token(t_mini *s)
{
	int i;

	i = 0;
	if (!(s->line = ft_calloc(3 , sizeof(char **))))
		error(s, ERR_CALLOC);
	s->line[0] = s->read.buf;
	if (!(s->line[1] = ft_calloc(ft_strlen(s->line[0]), sizeof(char))))
		error(s, ERR_CALLOC);
	while (s->line[0][i])
	{
		if (ft_isc)
	}

	ft_printf("-----break_cmdline_into_token-----\n");
	s->i = 0;

}

int is_char_set(int c, const char *char_set)
{
        int i;
        int len;

        i = 0;
        len = ft_strlen(char_set);
        while (i < len)
        {
                if (c == char_set[i])
                        return (1);
                i++;
        }
        return (0);
}
