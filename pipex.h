/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariling <ariling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 01:18:43 by ariling           #+#    #+#             */
/*   Updated: 2024/09/08 01:32:17 by ariling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_pipex
{
	int	pipefd[2];
	int	infile;
	int	outfile;
}		t_pipex;

// Function declarations
void	handle_error(const char *msg);
void	fork_and_exec(t_pipex *pipex, int is_first, char *cmd);
void	handle_redirection(t_pipex *pipex, int is_first);
void	execute_command(char *cmd);
void	wait_for_children(void);
int		open_file(const char *filename, int mode);
void	close_fds(int infile, int outfile, int pipefd[2]);

#endif
