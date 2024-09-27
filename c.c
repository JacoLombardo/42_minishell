#include "minishell.h"

void	print_tokens(char **tokens) // for testing
{
	int i, j;

	i = 0;
	while (tokens[i])
	{
		printf("\t%s\n", tokens[i]);
		i++;
	}
}

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int		is_bash_valid(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void	replace_vars(char *line, char *env[])
{
	// go through line
	// when i find $
		// copy whats after the $ in a temp "search" string (variable name). with a =
		// strnstr with env[i], search, strlen(env[i]). returns start of the match
		// value = return above + strlen(variable name)
	int		i;
	int		j;
	int		var_name_len;
	char	*var_name;
	char	*var_value;
	char	*new_line;

	i = 0;
	var_name_len = 0;
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
			var_name = ft_substr(line, i - var_name_len, var_name_len);
			var_name = ft_strjoin(var_name, "=");
			// replace 
			j = 0;
			while (env[j])
			{
				var_value = ft_strnstr(env[j], var_name, ft_strlen(env[j]));
				if (!var_value)
					j++;
				else
				{
					printf("found: %s\n", var_value + var_name_len + 1);
					break;
				}
			}
			var_name_len = 0;
		}
		i++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	// int		i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
	char	line1[] =  "arg1 arg2 \"$PAPAFRITA\""; // quotes no space. 3
	char	line2[] =  "hello i am $USER and this is $FRIEND"; // quotes no spaces. 3
	char	line3[] =  "arg1 $arg2-arg3"; // no quotes. 2
	char	line4[] =  "arg1 \"arg2 arg3\""; // 2
	char	line5[] =  "arg1 ar\"g2\""; // ?

	char	**tokens;

	replace_vars(line1, env);
	replace_vars(line2, env);

	return (0);
}
