/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:22:21 by mlapique          #+#    #+#             */
/*   Updated: 2024/04/13 16:18:07 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_free(t_pipex p)
{
	int	i;

	i = 0;
	close(p.infile);
	close(p.outfile);
	if (p.pid2 == 0)
	{
		close(p.tube[1]);
		close(p.tube[0]);
	}
	while (p.the_paths[i])
	{
		free(p.the_paths[i]);
		i++;
	}
	free(p.the_paths);
}

void	tine_free(t_pipex p)
{
	int	i;

	i = 0;
	while (p.the_args[i])
	{
		if (p.the_args[i])
			free(p.the_args[i]);
		i++;
	}
	free(p.the_args);
}

int	child(t_pipex p, int argc)
{
	if (close(p.tube[0]) == -1)
		return (close(p.tube[1]), -1);
	if (p.index == 2)
		if (dup2(p.infile, STDIN_FILENO) == -1)
			return (close(p.tube[1]), -1);
	if (p.index == argc - 2)
	{
		if (dup2(p.outfile, STDOUT_FILENO) == -1)
			return (close(p.tube[1]), -1);
	}
	else
	{
		if (dup2(p.tube[1], STDOUT_FILENO) == -1)
			return (close(p.tube[1]), -1);
	}
	return (0);
}

void	p_function(t_pipex p, char *argv[], char *env[], int argc)
{
	p.index = 2;
	while (p.index <= argc - 2)
	{
		if (pipe(p.tube) < 0)
			error(ERR_PIPE, ERR_OUT);
		p.pid2 = fork();
		if (p.pid2 == -1)
			return ;
		if (p.pid2 == 0)
		{
			if (child(p, argc) == -1)
				return ;
			do_the_thing(p, argv, env, p.index);
			fork_free(p);
			exit(1);
		}
		else
		{
			waitpid(p.pid2, NULL, 0);
			if ((close(p.tube[1]) == -1
					|| dup2(p.tube[0], 0) == -1 || close(p.tube[0]) == -1))
				return ;
		}
		p.index++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	p;
	int		i;

	i = 0;
	p.cmd = NULL;
	if (argc < 5)
		return (error(TOO_MUCH_ARGC, STD_OUT), 1);
	i = 0;
	p.infile = open(argv[1], O_RDONLY);
	if (p.infile < 0)
		error(ERR_INFILE, ERR_OUT);
	p.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (p.outfile < 0)
		error(ERR_OUTFILE, ERR_OUT);
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	p.paths = ft_substr(env[i], 5, ft_strlen(env[i]));
	p.the_paths = ft_split(p.paths, ':');
	if (p.the_paths == NULL)
		return (0);
	free(p.paths);
	p_function(p, argv, env, argc);
	p.pid2 = -9;
	fork_free(p);
	return (0);
}
