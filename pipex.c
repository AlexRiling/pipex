/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariling <ariling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 01:18:49 by ariling           #+#    #+#             */
/*   Updated: 2024/09/08 02:03:24 by ariling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

extern char	**environ;

void	execute_command(char *cmd)
{
	char	*cmd_args[4];

	cmd_args[0] = "/bin/sh";
	cmd_args[1] = "-c";
	cmd_args[2] = cmd;
	cmd_args[3] = NULL;
	if (execve("/bin/sh", cmd_args, environ) == -1)
	{
		handle_error("execve");
	}
}

void	handle_redirection(t_pipex *pipex, int is_first)
{
	if (is_first)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->pipefd[0]);
	}
	else
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->pipefd[1]);
	}
}

void	fork_and_exec(t_pipex *pipex, int is_first, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		handle_error("fork");
	}
	if (pid == 0)
	{
		handle_redirection(pipex, is_first);
		execute_command(cmd);
	}
}

void	wait_for_children(void)
{
	wait(NULL);
	wait(NULL);
}

int	main(int argc, char *argv[])
{
	t_pipex	pipex;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		return (1);
	}
	pipex.infile = 0;
	pipex.outfile = 0;
	pipex.infile = open_file(argv[1], O_RDONLY);
	pipex.outfile = open_file(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (pipe(pipex.pipefd) == -1)
	{
		handle_error("pipe");
	}
	fork_and_exec(&pipex, 1, argv[2]);
	fork_and_exec(&pipex, 0, argv[3]);
	close_fds(pipex.infile, pipex.outfile, pipex.pipefd);
	wait_for_children();
	return (0);
}
