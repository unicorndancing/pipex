
#include "pipex.h"

void	fork_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->the_paths[i])
	{
		free(pipex->the_paths[i]);
		i++;
	}
	free(pipex->the_paths);
}

void	tine_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->the_args[i])
	{
		free(pipex->the_args[i]);
		i++;
	}
	free(pipex->the_args);
	free(pipex->cmd);
}

void	pipex_function(t_pipex pipex, char *argv[], char *env[], int argc)
{
	int	i;

	i = 2;
	dup2(pipex.infile, 0);
	while (i < argc - 2)
	{
		pipex.pid2 = fork();
		if (pipex.pid2 == -1)
			exit(1);
		if (pipex.pid2)
		{
			close(pipex.mariotube[0]);
			dup2(pipex.mariotube[1], 1);
			do_the_thing(pipex, argv, env, i);
		}
		else
		{
			close(pipex.mariotube[1]);
			dup2(pipex.mariotube[0], 0);
		}
		i++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		i;

	if (argc < 5)
		return (error(TOO_MUCH_ARGC, STD_OUT), -1);
	i = 0;
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		error(ERR_INFILE, ERR_OUT);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (pipex.outfile < 0)
		error(ERR_OUTFILE, ERR_OUT);
	if (pipe(pipex.mariotube) < 0)
		error(ERR_PIPE, ERR_OUT);
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	pipex.paths = ft_substr(env[i], 5, ft_strlen(env[i]));
	pipex.the_paths = ft_split(pipex.paths, ':');
	pipex_function(pipex, argv, env, argc);
	dup2(pipex.outfile, 1);
	do_the_thing(pipex, argv, env, argc - 2);
	fork_free(&pipex);
	tine_free(&pipex);
	return (0);
}
