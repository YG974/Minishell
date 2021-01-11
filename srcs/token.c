#include "../libft/libft.h"
#include "../includes/minishell.h"

/*
 ** cmd->str = command line;
 * cmd->flag = flags or comments;
 * cmd->str[i] = char i of the line;
 * cmd->flag[i] = flags or comments on char i;
 * flags :
 * 1 : inside simpled quotes
 * 2 : inside double quotes
 * 3 : escaped by backslash
 * 4 : dollar expansion
 */

void check_dollars(t_mini *s, t_cmdl *cmd)
{
	s->i = 0;
	while (cmd->str[s->i])
	{
		if (cmd->str[s->i] == '$' && cmd->flag[s->i] != '1'
				&& cmd->str[s->i - 1] != '\\')
		{
				cmd->flag[s->i] = '4';
				s->i++;
			while (cmd->str[s->i]
					&& (ft_isalnum(cmd->str[s->i])
					|| cmd->str[s->i] == '_'))
			{
				cmd->flag[s->i] = '4';
				s->i++;
			}
		}
		else
			s->i++;
	}
}


void check_double_quotes(t_mini *s, t_cmdl *cmd)
{
	if (cmd->str[s->i - 1] == '\\')
	{
		cmd->flag[s->i] = '3';
		s->i++;
	}
	else
	{
		s->i++;
		while (cmd->str[s->i] != '\"' && cmd->str[s->i])
		{
			cmd->flag[s->i] = '2';
			s->i++;
			if (cmd->str[s->i] == '\0')
				error (s, ERR_QUOTES);
		}
		s->i++;
	}
}

void check_simple_quotes(t_mini *s, t_cmdl *cmd)
{
	if (cmd->str[s->i - 1] == '\\')
	{
		cmd->flag[s->i] = '3';
		s->i++;
	}
	else
	{
		s->i++;
		while (cmd->str[s->i] != '\'' && cmd->str[s->i])
		{
			cmd->flag[s->i] = '1';
			s->i++;
			if (cmd->str[s->i] == '\0')
				error (s, ERR_QUOTES);
		}
		s->i++;
	}
}

void check_quotes(t_mini *s, t_cmdl *cmd)
{
	s->i = 0;
	while (cmd->str[s->i])
	{
		if (cmd->str[s->i] == '\"')
			check_double_quotes(s, cmd);
		else if (cmd->str[s->i] == '\'')
			check_simple_quotes(s, cmd);
		else
			s->i++;
	}
}

void break_cmdline_into_token(t_mini *s)
{
	int i;
	t_cmdl	*cmd;

	cmd = s->firstcmdl;
	while (cmd)
	{
		i = -1;
		cmd->flag = ft_strdup(cmd->str);
		while (cmd->flag && cmd->flag[++i])
			cmd->flag[i] = '0';
		check_quotes(s, cmd);
		ft_printf("%s\n", cmd->flag);
		ft_printf("%s\n", cmd->str);
		check_dollars(s, cmd);
		ft_printf("%s\n", cmd->flag);
		ft_printf("%s\n", cmd->str);
		cmd =cmd->next;
	}
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
