/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:22:21 by mlapique          #+#    #+#             */
/*   Updated: 2024/04/06 17:22:56 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (pipex->the_args[i])
			free(pipex->the_args[i]);
		i++;
	}
	free(pipex->the_args);
	free(pipex->cmd);
}

void	child(t_pipex pipex, char *argv[], char *env[], int argc)
{
	if (pipex.index == argc - 2)
	{
		close(pipex.mariotube[0]);
		dup2(pipex.outfile, 1);
		do_the_thing(pipex, argv, env, argc - 2);
	}
	else
	{
		close(pipex.mariotube[0]);
		dup2(pipex.mariotube[1], 1);
		do_the_thing(pipex, argv, env, pipex.index);
	}
}

void	pipex_function(t_pipex pipex, char *argv[], char *env[], int argc)
{
	pipex.index = 2;
	dup2(pipex.infile, 0);
	while (pipex.index < argc - 1)
	{
		if (pipe(pipex.mariotube) < 0)
			error(ERR_PIPE, ERR_OUT);
		pipex.pid2 = fork();
		if (pipex.pid2 == -1)
			exit(1);
		if (pipex.pid2)
			child(pipex, argv, env, argc);
		else
		{
			close(pipex.mariotube[1]);
			dup2(pipex.mariotube[0], 0);
		}
		pipex.index++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		i;

	i = 0;
	if (argc < 5)
		return (error(TOO_MUCH_ARGC, STD_OUT), -1);
	i = 0;
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		error(ERR_INFILE, ERR_OUT);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (pipex.outfile < 0)
		error(ERR_OUTFILE, ERR_OUT);
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	pipex.paths = ft_substr(env[i], 5, ft_strlen(env[i]));
	pipex.the_paths = ft_split(pipex.paths, ':');
	pipex_function(pipex, argv, env, argc);
	close(pipex.infile);
	close(pipex.outfile);
	fork_free(&pipex);
	free(pipex.paths);
	return (0);
}
