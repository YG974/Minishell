#include "../libft/libft.h"
#include "../includes/minishell.h"

int		ft_ismeta(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

char	*ft_strdup_quotes(char *src, char *flagstr, char c)
{
	int		i;
	int		len;
	char	*dest;

	len = 0;
	i = 0;
	while (flagstr[len] && flagstr[len] == c)
		len++;
	len = ft_inc_i(src, src, 0, c);
	if (!(dest = calloc(len, sizeof(char))))
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_inc_i(char *str, char *flag, int i, char c)
{
	if (c == '1')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
		return (i);
	} else if (c == '2')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
		return (i);
	}
	if (str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
		return (i);
	}
	if (str[i] && ft_ismeta(str[i]))
		i++;
	else
		while (str[i] && !ft_ismeta(str[i]) && flag[i] == '0')
			i++;
	return (i);
}
