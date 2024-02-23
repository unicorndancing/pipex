
#include "pipex.h"

char	*get_command(char **paths, char *cmd, t_pipex pipex)
{
	while (*paths)
	{
		pipex.tmp = ft_strjoin(*paths, "/");
		pipex.command = ft_strjoin(pipex.tmp, cmd);
		free(pipex.tmp);
		if (access(pipex.command, 0) == 0)
			return (pipex.command);
		free(pipex.command);
		paths++;
	}
	return (NULL);
}

void	tine1(t_pipex pipex, char *argv[], char *env[])
{
	dup2(pipex.mariotube[1], 1);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_command(pipex.cmd_paths, pipex.cmd_args[0], pipex);
	if (!pipex.cmd)
	{
		tine_free(&pipex);
		error(ERR_CMD, STD_OUT);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, env);
}

void	tine2(t_pipex pipex, char *argv[], char *env[])
{
	dup2(pipex.mariotube[0], 0);
	close(pipex.mariotube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0], pipex);
	if (!pipex.cmd)
	{
		tine_free(&pipex);
		error(ERR_CMD, STD_OUT);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, env);
}

void	error(char *error_message, int error_or_perror)
{
	if (error_or_perror == 2)
		ft_putendl_fd(error_message, 2);
	else
	{
		perror(error_message);
		exit(1);
	}
}