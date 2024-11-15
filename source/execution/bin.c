/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:09:40 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/15 16:13:05 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_test(char *filename)
{	
	struct stat statbuf;

    // Get the file status using stat
    if (stat(filename, &statbuf) == -1) {
        perror("stat failed");
        return EXIT_FAILURE;
    }

    // Check if it's a directory
    if (S_ISDIR(statbuf.st_mode)) {
        printf("'%s' is a directory\n", filename);
    }
    // Check if it's a regular file and executable
    else if (S_ISREG(statbuf.st_mode)) {
        printf("'%s' is a regular file\n", filename);

        // Check for executable permissions (user, group, others)
        if (statbuf.st_mode & S_IXUSR) {
            printf("File is executable by the user\n");
        } else {
            printf("File is not executable by the user\n");
        }

        if (statbuf.st_mode & S_IXGRP) {
            printf("File is executable by the group\n");
        } else {
            printf("File is not executable by the group\n");
        }

        if (statbuf.st_mode & S_IXOTH) {
            printf("File is executable by others\n");
        } else {
            printf("File is not executable by others\n");
        }

        // Check if the file has no permissions
        if (!(statbuf.st_mode & (S_IRUSR | S_IWUSR | S_IXUSR)) &&
            !(statbuf.st_mode & (S_IRGRP | S_IWGRP | S_IXGRP)) &&
            !(statbuf.st_mode & (S_IROTH | S_IWOTH | S_IXOTH))) {
            printf("File has no read, write, or execute permissions\n");
        }
    }
    else {
        printf("'%s' is neither a regular file nor a directory\n", filename);
    }

    return EXIT_SUCCESS;
}

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = 0;
	allpath = ft_split(ft_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_both_tab(allpath, s_cmd);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_both_tab(allpath, s_cmd);
	return (NULL);
}

int	ft_is_function(char *path)
{
	struct stat	statbuf;

	ft_memset(&statbuf, 0, sizeof(statbuf));
	stat(path, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		if ((path[0] == '.' && path[1] == '/') || path[0] == '/')
			return (ft_file_error(path, 2));
		else
			return (ft_file_error(path, 1));
	}
	else if (S_ISREG(statbuf.st_mode))
	{
		if (!ft_strncmp(path, "./", 2))
			return (ft_file_error(path, 3));
		else
			return (ft_file_error(path, 1));
	}
	else
	{
		if (path[0] == '/' || (path[0] == '.' && path[1] == '/'))
			return (ft_file_error(path, 4));
		else
			return (ft_file_error(path, 1));
	}
}

void	ft_bin_child(t_full_cmd *cmd, t_data *data, int status, char *path)
{
	if (cmd->redirections)
		status = ft_redirect(cmd->redirections, cmd->targets, data);
	if (status == 1)
	{
		free(path);
		ft_free_cmd(cmd);
		ft_free_tab(data->env);
		exit(status);
	}
	if (execve(path, cmd->args, data->env) == -1)
		ft_error(cmd->cmd, 1);
}

int	ft_bin(t_full_cmd *cmd, t_data *data, int status)
{
	char	*path;
	pid_t	pid;

	path = ft_get_path(cmd->cmd, data->env);
	if (!path)
		return (ft_is_function(cmd->cmd));
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		ft_bin_child(cmd, data, status, path);
	else
	{
		free(path);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (status);
}
