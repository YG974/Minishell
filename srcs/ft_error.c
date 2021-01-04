#include "../libft/libft.h"
#include "../includes/minishell.h"

void error(t_mini *s, int error)
{
	int	ret;

	s->status = 1;
	if (error == ERR_CALLOC)
		ret = ft_printf("Memory Allocation fail\n");
	if (error == ERR_PARSING)
		ret = ft_printf("Parsing fail\n");
	if (error == ERR_QUOTES)
		ret = ft_printf("Parsing fail, quote not close\n");
}
