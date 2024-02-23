
#include "pipex.h"

void	fork_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	tine_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}


void	pipex_function(t_pipex pipex, char *argv[], char *env[])
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	pipex.paths = ft_substr(env[i], 5, ft_strlen(env[i]));
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		tine1(pipex, argv, env);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		tine2(pipex, argv, env);
	close(pipex.mariotube[0]);
	close(pipex.mariotube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	fork_free(&pipex);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc != 5)
	{
		error(TOO_MUCH_ARGC, STD_OUT);
		return (-1);
	}
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		error(ERR_INFILE, ERR_OUT);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR);
	if (pipex.outfile < 0)
		error(ERR_OUTFILE, ERR_OUT);
	if (pipe(pipex.mariotube) < 0)
		error(ERR_PIPE, ERR_OUT);
	pipex_function(pipex, argv, env);
	return (0);
}
