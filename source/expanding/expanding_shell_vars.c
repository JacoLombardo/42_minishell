#include "../../includes/parsing.h"

static char	*ft_get_temp_var_filename(t_data *data)
{
	return ft_charjoin("/tmp/vars_temp", data->shell_id + '0');
}

static char	**append_to_env(char **new_env, char *line)
{
	char	**newer_env;
	int		len;

	len = ft_tablen(new_env);
	newer_env = ft_reallocenv(new_env, len);
	newer_env[len] = line;
	return (newer_env);
}

char	**copy_and_enhance_env(t_data *data)
{
	char	**new_env;
	char	*file;
	char	*line;
	int		fd;

	file = ft_get_temp_var_filename(data);
	new_env = ft_cpyenv(data->env);
	fd = open(file, O_RDONLY, 0777);
	free(file);
	if (!fd)
		return (new_env);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		new_env = append_to_env(new_env, line);
		free(line);
	}
	return (new_env);
}
void	ft_var_to_temp(char *var, t_data *data)
{
	int		fd;
	char	*temp;

	temp = ft_get_temp_var_filename(data);
	fd = open(temp, O_CREAT | O_WRONLY | O_APPEND, 0777);
	free(temp);
	ft_putstr_fd(var, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}

char	*ft_temp_to_env(char *var, t_data *data)
{
	int		fd;
	char	*line;
	char	*content;
	char	*temp;

	content = NULL;
	temp = ft_get_temp_var_filename(data);
	fd = open(temp, O_RDONLY, 0777);
	free(temp);
	if (fd < 0)
		return (content);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_find_var(line, var))
			content = ft_strndup(line, (ft_strlen(line) - 1));
		free(line);
	}
	close(fd);
	return (content);
}
