/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:08:29 by mbah              #+#    #+#             */
/*   Updated: 2025/02/01 00:10:57 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

int	main(int argc, char **argv)
{
	int		fd[2];
	pid_t	pid;
	char	buffer[12];

	(void)argv;
	if (argc < 2)
		exit(-1);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		printf("---------- (Le processus enfant commence) ---------\n");
		close(fd[0]);
		write(fd[1], "mbah42\n", 7);
		close(fd[1]);
		sleep(5);
		printf("---------- (Le processus enfant termine) ---------\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("---------- (Le processus parent commence) ---------\n");
		wait(NULL);
		close(fd[1]);
		read(fd[0], buffer, 7);
		close(fd[0]);
		printf("le fils a ecrit : %s\n", buffer);
		printf("---------- (Le processus parent termine) ---------\n");
		exit(EXIT_SUCCESS);
	}
	/*fd = open("exemple.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (access("example.txt", W_OK))
		printf("autorisé\n");
	execve("/bin/cat", argv + 1, NULL);
	printf("%s\n", argv[1]);
	*/
	return (0);
}
