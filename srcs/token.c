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

char *get_env_value(t_mini *s, char *name)
{
	char *value;
	t_env *env;
	int		i;

	value = ft_strdup("");
	env = s->env;
	i = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->name, name, i) == 0
				&& i == ft_strlen(env->name))
			return (env->value);
		env = env->next;
	}
	return (value);
}

void expand_dollars(t_mini *s, t_cmdl *cmd)
{
	char *tmp;
	char *buf;

	int j;
	s->i = 0;
	j = 0;
	while (cmd->str[s->i])
	{
		while (cmd->flag[s->i] != '4' && cmd->str[s->i])
			s->i++;
		buf = ft_strdup_size(cmd->str, s->i, 0);
		//ft_printf("%d %d\n", s->i, j);
		while (cmd->flag[s->i++] == '4' && cmd->str[s->i + 1] != '$'
				&& cmd->str[s->i])
			j++;
		tmp = ft_strdup_size(cmd->str, s->i, s->i - j);
		tmp = get_env_value(s, tmp);
		ft_printf("buf :%d-%d :%s|\n", s->i, s->i - j, buf);
		ft_printf("tmp :%s|\n", tmp);
		//ft_printf("%d %d\n", s->i, j);
	}


}

void check_dollars(t_mini *s, t_cmdl *cmd)
{
	s->i = 0;
	while (cmd->str[s->i])
	{
		if (cmd->str[s->i] == '$' && cmd->flag[s->i] != '1'
				&& cmd->str[s->i - 1] != '\\')
		{
				cmd->flag[s->i++] = '4';
			while (cmd->str[s->i]
					&& (ft_isalnum(cmd->str[s->i])
					|| cmd->str[s->i] == '_'))
				cmd->flag[s->i++] = '4';
		}
		else
			s->i++;
	}
}


void check_double_quotes(t_mini *s, t_cmdl *cmd)
{
	if (cmd->str[s->i - 1] == '\\')
		cmd->flag[s->i++] = '3';
	else
	{
		cmd->flag[s->i++] = '2';
		while (cmd->str[s->i] != '\"' && cmd->str[s->i])
		{
			cmd->flag[s->i++] = '2';
			if (cmd->str[s->i] == '\0')
				error (s, ERR_QUOTES);
		}
		cmd->flag[s->i++] = '2';
	}
}

void check_simple_quotes(t_mini *s, t_cmdl *cmd)
{
	if (cmd->str[s->i - 1] == '\\')
		cmd->flag[s->i++] = '3';
	else
	{
		cmd->flag[s->i++] = '1';
		while (cmd->str[s->i] != '\'' && cmd->str[s->i])
		{
			cmd->flag[s->i++] = '1';
			if (cmd->str[s->i] == '\0')
				error (s, ERR_QUOTES);
		}
		cmd->flag[s->i++] = '1';
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
		check_dollars(s, cmd);
		ft_printf("-----------\n", cmd->flag);
		ft_printf("%s\n", cmd->flag);
		ft_printf("%s\n", cmd->str);
		expand_dollars(s, cmd);
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
