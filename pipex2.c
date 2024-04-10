/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:21:54 by mlapique          #+#    #+#             */
/*   Updated: 2024/04/10 16:27:25 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command(char **paths, char *cmd, t_pipex pipex)
{
	int	i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (paths[i])
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

void	do_the_thing(t_pipex pipex, char *argv[], char *env[], int i)
{
	pipex.the_args = ft_split(argv[i], ' ');
	pipex.cmd = get_command(pipex.the_paths, pipex.the_args[0], pipex);
	if (!pipex.cmd)
	{
		perror(pipex.cmd);
	}
	else if (execve(pipex.cmd, pipex.the_args, env) == -1)
	{
		perror("execve");
	}
	tine_free(pipex);
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
