# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct	s_truc
{
	char *buf;
	char **str;
}				t_truc;

int main(int argc, char **argv)
{
	t_truc	test;
	int fd[2];
	int fdtwo[2];
	int i;
	char	buffer[BUFFER_SIZE + 1];
	// fd 0 read
	// fd 1 write

	ft_bzero(&buffer, BUFFER_SIZE + 1);
	test.buf = ft_strdup("test1 test2");
	test.str = ft_split(test.buf, ' ');
	free(test.buf);
	if (pipe(fd) == -1)
		return (1);
	int pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		ft_putstr_fd(test.str[0], fd[1]);
		printf("ceci est l'enfant et sa phrase est : %s\n", test.str[0]);
		close(fd[1]);
		//printf("TESTTEST\n");
	} else
	{
		close(fd[1]);
		//kill(pid, SIGKILL);
		waitpid(pid, NULL, 0);
		if (pipe(fdtwo) == -1)
			return (1);
		int pidtwo = fork();
		if (pidtwo == 0)
		{
			close(fdtwo[0]);
			read(fd[0], buffer, BUFFER_SIZE);
			i = printf("Ceci est le parent, on lit donc la phrase de l'enfant : %s\nEt la phrase du parent : %s\n", buffer, test.str[1]);
			write(fdtwo[1], &i, sizeof(int));
			printf("On envoie maintenant le retour de printf au deuxieme parent.\n");
			close(fdtwo[1]);
		} else
		{
			close(fdtwo[1]);
			waitpid(pidtwo, NULL, 0);
			int y;
			read(fdtwo[0], &y, sizeof(int));
			printf("Le retour du printf du premier parent est : %d\nFIN", y);
			close(fdtwo[0]);
		}
		close(fd[0]);
	}
	free(test.str[0]);
	free(test.str[1]);
	free(test.str);
	return (0);
}
