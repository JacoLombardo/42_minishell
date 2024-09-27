#include "minishell.h"

void	print_tokens(char **tokens) // for testing
{
	int i, j;

	i = 0;
	while (tokens[i])
	{
		printf("\t token %d : %s\n", i + 1, tokens[i]);
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

char	*replace_vars(char *line, char *env[])
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
			free(var_name); // if i move this to after line 53, i go from "9 allocs 7 frees" to 9/9, but i get a bunch of errors and there are still leaks
			var_name_len = 0;
		}
		// this little block below makes the string work fine but has bazillion allocs that are not freed. 59 allocs / 32 frees
		temp = ft_strdup(new_line);
		free(new_line);
		hold_char[0] = line[i];
		hold_char[1] = '\0'; // if i dont do this this way, the final new line has an extra random character after each real one
		new_line = ft_strjoin(temp, hold_char);
		free(temp);
		i++;
	}
	return (new_line);
}

int	main(int argc, char *argv[], char *env[])
{
	char	line1[] =  "arg1 arg2 \"$PAPAFRITA\""; // quotes no space. 3
	char	*line2 =  ft_strdup("hello i am $USER and this is $FRIEND"); // quotes no spaces. 3
	char	line3[] =  "arg1 $arg2-arg3"; // no quotes. 2
	char	line4[] =  "arg1 \"arg2 arg3\""; // 2
	char	line5[] =  "arg1 ar\"g2\""; // ?
	char	*line6;
	char	**tokens;
	int		i = 0;

	printf("%s\n", line2);
	line6 = replace_vars(line2, env);
	free(line2);
	tokens = get_tokens(line6);
	print_tokens(tokens);
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	free(line6);

	return (0);
}
