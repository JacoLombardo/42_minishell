#include "minishell.h"

void	print_ttoken(t_token *token)
{
	printf("value: %s\ttype: %i. ", token->value, token->type);
	if (!token->next)
		printf("this is the last one");
	printf("\n");
}

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}

int		is_bash_valid(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (TRUE);
	return (FALSE);
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

int	main(int argc, char *argv[], char *env[])
{
	char	*line2 =  ft_strdup("hello i || >> am < $USER > and this is $FRIEND"); // quotes no spaces. 3

	char	*line6;
	int		i = 0;
	t_token *token_list;

	line6 = replace_vars(line2, env);
	free(line2);
	tokenize(line6);
	while (token_list->next != NULL)
	{
		print_ttoken(token_list);
		token_list = token_list->next;
	}
	print_ttoken(token_list);

	free(line6);
	free_token_list(find_first(token_list));

	return (0);
}
