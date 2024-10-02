#include "minishell.h"

char	*expand_vars(char *line, char *env[])
{
	int		j;
	int		i;
	int		var_name_len;
	char	*var_name;
	char	*var_value;
	char	*new_line;
	char	*temp;
	char	hold_char[2];

	i = 0;
	var_name_len = 0;
	new_line = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && what_quotes(line + i + 1) != 2)
		{
			i++;
			while(is_bash_valid(line[i]))
			{
				var_name_len++;
				i++;
			}
			temp = ft_substr(line, i - var_name_len, var_name_len);
			var_name = ft_strjoin(temp, "=");
			free(temp);
			// replace 
			j = 0;
			while (env[j])
			{
				var_value = ft_strnstr(env[j], var_name, ft_strlen(env[j]));
				if (!var_value)
					j++;
				else
				{
					temp = ft_strdup(new_line); // should be newline??
					free(new_line);
					new_line = ft_strjoin(temp, var_value + var_name_len + 1);
					free(temp);
					break;
				}
			}
			free(var_name);
			var_name_len = 0;
		}
		temp = ft_strdup(new_line);
		free(new_line);
		hold_char[0] = line[i];
		hold_char[1] = '\0';
		new_line = ft_strjoin(temp, hold_char);
		free(temp);
		i++;
	}
	return (new_line);
}
