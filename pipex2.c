/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:21:20 by mlapique          #+#    #+#             */
/*   Updated: 2024/03/20 14:21:24 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command(char **paths, char *cmd, t_pipex pipex)
{
	int	i;

	i = 0;
	while (*paths[i])
	{
		pipex.tmp = ft_strjoin(paths[i], "/");
		pipex.command = ft_strjoin(pipex.tmp, cmd);
		free(pipex.tmp);
		if (access(pipex.command, 0) == 0)
			return (pipex.command);
		free(pipex.command);
		i++;
	}
	return (NULL);
}

void	tine1(t_pipex pipex, char *argv[], char *env[])
{
	printf("tine1\n");
	dup2(pipex.mariotube[1], 1);
	dup2(pipex.infile, 0);
	pipex.the_args = ft_split(argv[2], ' ');
	pipex.cmd = get_command(pipex.the_paths, pipex.the_args[0], pipex);
	if (!pipex.cmd)
	{
		tine_free(&pipex);
		error(ERR_CMD, STD_OUT);
		exit(1);
	}
	execve(pipex.cmd, pipex.the_args, env);
}

void	tine2(t_pipex pipex, char *argv[], char *env[], int i)
{
	printf("tine2\n");
	dup2(pipex.mariotube[0], 0);
	dup2(pipex.mariotube[1], 1);
	pipex.the_args = ft_split(argv[i], ' ');
	pipex.cmd = get_command(pipex.the_paths, pipex.the_args[0], pipex);
	if (!pipex.cmd)
	{
		tine_free(&pipex);
		error(ERR_CMD, STD_OUT);
		exit(1);
	}
	execve(pipex.cmd, pipex.the_args, env);
}

void	tine3(t_pipex pipex, char *argv[], char *env[], int i)
{
	printf("tine3\n");
	dup2(pipex.mariotube[0], 0);
	close(pipex.mariotube[1]);
	dup2(pipex.outfile, 1);
	pipex.the_args = ft_split(argv[i], ' ');
	pipex.cmd = get_command(pipex.the_paths, pipex.the_args[0], pipex);
	if (!pipex.cmd)
	{
		tine_free(&pipex);
		error(ERR_CMD, STD_OUT);
		exit(1);
	}
	execve(pipex.cmd, pipex.the_args, env);
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