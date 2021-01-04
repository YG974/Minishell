#include "../libft/libft.h"
#include "../includes/minishell.h"

void error(t_mini *s, int error)
{
	int	ret;

	s->status = 0;
	if (error == ERR_CALLOC)
		ret = ft_printf("Memory Allocation fail");
}
