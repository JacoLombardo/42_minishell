#include "../includes/minishell.h"

char	*ft_charjoin(char const *str, char const c)
{
	size_t	len;
	char	*new;
	int		i;

	len = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		new[i] = str[i];
		i++;
	}
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
}
