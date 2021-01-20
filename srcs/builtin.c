#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_echo(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	(void)cmd;
	ft_printf("echo \n");
	return (0);
}

int		ft_cd(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	(void)cmd;
	ft_printf("cd \n");
	return (0);
}

int		ft_pwd(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	(void)cmd;
	ft_printf("pwd \n");
	return (0);
}

int		ft_export(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	(void)cmd;
	ft_printf("export \n");
	return (0);
}

int		ft_unset(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	(void)cmd;
	ft_printf("unset \n");
	return (0);
}

int		ft_env(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	(void)cmd;
	ft_printf("env \n");
	return (0);
}

int		ft_exit(t_mini *s, t_cmdl *cmd)
{
	(void)s;
	(void)cmd;
	ft_printf("exit \n");
	return (WANT_EXIT);
}
