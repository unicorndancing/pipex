/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:11:04 by mlapique          #+#    #+#             */
/*   Updated: 2024/04/06 18:56:58 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "libft/libft.h"

# define ERR_INFILE "Infile bug, need some liber.... tea"
# define ERR_OUTFILE "Outfile bug"
# define TOO_MUCH_ARGC "too BIG or too little arg sowwy UwU.\n"
# define ERR_PIPE "Pipe_error don't really know"
# define ERR_CMD "learn too type your command, or parsing error I don't know"

enum e_enum
{
	STD_OUT = 2,
	ERR_OUT = 10
};

typedef struct s_pipex
{
	char	*paths;
	char	**the_paths;
	char	**the_args;
	char	*cmd;
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	int		mariotube[2];
	int		infile;
	int		outfile;
	int		index;
	char	*tmp;
	char	*command;
}t_pipex;

/* childs.c */
void	do_the_thing(t_pipex pipex, char *argv[], char *env[], int i);
void	tine2(t_pipex pipex, char *argv[], char *envp[], int i);
void	tine3(t_pipex pipex, char *argv[], char *env[], int i);

/* free.c */
void	fork_free(t_pipex pipex);
void	tine_free(t_pipex pipex);

/* error.c */
void	error(char *error_message, int fd);

#endif
