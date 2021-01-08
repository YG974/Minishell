#include "../libft/libft.h"
#include "../includes/minishell.h"

/*
 ** s->line[0] = command line;
 * s->line[1] = flags or comments;
 * s->line[0][i] = char i of the line;
 * s->line[1][i] = flags or comments on char i;
 * 
 */
void check_double_quotes(t_mini *s)
{
	if (s->line[0][s->i - 1] == '\\')
	{
		s->line[1][s->i] = '3';
		s->i++;
	}
	else
	{
		s->i++;
		while (s->line[0][s->i] != '\"' && s->line[0][s->i])
		{
			s->line[1][s->i] = '2';
			if (s->line[0][s->i] == '\0')
				error (s, ERR_QUOTES);
			s->i++;
		}
		s->i++;
	}
}void check_simple_quotes(t_mini *s)
{
	if (s->line[0][s->i - 1] == '\\')
	{
		s->line[1][s->i] = '3';
		s->i++;
	}
	else
	{
		s->i++;
		while (s->line[0][s->i] != '\'' && s->line[0][s->i])
		{
			s->line[1][s->i] = '1';
			if (s->line[0][s->i] == '\0')
				error (s, ERR_QUOTES);
			s->i++;
		}
		s->i++;
	}
}
void check_quotes(t_mini *s)
{
	s->i = 0;
	while (s->line[0][s->i])
	{
		if (s->line[0][s->i] == '\"')
			check_double_quotes(s);
		else if (s->line[0][s->i] == '\'')
			check_simple_quotes(s);
		else
			s->i++;
	}
	ft_printf("%s\n", s->line[0]);
	ft_printf("%s\n", s->line[1]);
}
void break_cmdline_into_token(t_mini *s)
{
	int i;
	char c;

	i = -1;
	c = '0';
	ft_printf("-----break_cmdline_into_token-----\n");
	if (!(s->line = ft_calloc(3 , sizeof(char **))))
		error(s, ERR_CALLOC);
	s->line[0] = s->read.buf;
	s->line[1] = ft_strdup(s->line[0]);
	while (s->line[1] && s->line[1][++i])
		s->line[1][i] = '0';
	ft_printf("%s\n", s->line[0]);
	ft_printf("%s\n", s->line[1]);
	check_quotes(s);
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
