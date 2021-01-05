#include "../libft/libft.h"
#include "../includes/minishell.h"

void error(t_mini *s, int error)
{
	int	ret;

	s->status = 0;
	if (error == ERR_CALLOC)
		ret = ft_printf("Memory Allocation fail\n");
	if (error == ERR_INVALID_ENV_NAME)
		ret = ft_printf("invalid variable name or value\n");
}
