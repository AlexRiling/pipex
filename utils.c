/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariling <ariling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 01:18:39 by ariling           #+#    #+#             */
/*   Updated: 2024/09/08 02:00:21 by ariling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Function to handle errors and print messages
void	handle_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

// Function to open files with proper error handling
int	open_file(const char *filename, int mode)
{
	int	fd;

	fd = open(filename, mode, 0644);
	if (fd < 0)
	{
		handle_error(filename);
	}
	return (fd);
}

void	close_fds(int infile, int outfile, int pipefd[2])
{
	close(infile);
	close(outfile);
	close(pipefd[0]);
	close(pipefd[1]);
}
