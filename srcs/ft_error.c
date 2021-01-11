#include "../libft/libft.h"
#include "../includes/minishell.h"

void error(t_mini *s, int error)
{
	int	ret;

	s->error = 1;
	if (error == ERR_CALLOC)
		ret = ft_printf("Memory Allocation fail\n");
	if (error == ERR_INVALID_ENV_NAME)
		ret = ft_printf("invalid variable name or value\n");
	if (error == ERR_PARSING)
		ret = ft_printf("Parsing fail\n");
	if (error == ERR_QUOTES)
		ret = ft_printf("Parsing fail, quote not close\n");
	if (error == ERR_SEMCOL)
		ret = ft_printf("Bad using of ';'. Retry mother fucker.\n");
}
