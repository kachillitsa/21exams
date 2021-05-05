#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
void	err_args()
{
	write(2, "error: cd: bad arguments\n", 26);
}

void	err_fatal(void)
{
	write(2, "error: fatal\n", 14);
	exit(1);
}

void	err_path(char *line)
{
	write(2, "error: cd: cannot change directory to ", 39);
	write(2, line, ft_strlen(line));
	write(2, "\n", 1);
}

int		count_args(char **av, int i)
{
	int len = 0;
	while (av[i] && strcmp(av[i], ";") && strcmp(av[i], ";")) {
		i++;
		len++;
	}
	return len;
}

void	ft_cd(char **line)
{
	int i = 0;
	while (line[i]) i++;
	if (i != 2) {
		err_args();
		return;
	}
	if (chdir(line[1]))
	{
		err_path(line[1]);
		return;
	}
}

int main (int ac, char **av, char **env)
{
	int i = 1;
	int len;
	char **line = NULL;
	int	a_l = 0;
	int op = 0;

	if (ac <= 1)
		return(0);
	while (i < ac)
	{
		while (!(strcmp(av[i], ";")) || !(strcmp(av[i], "|")))
		{
			i++;
			continue;
		}
		len = count_args(av, i);
		line = malloc(sizeof(char *) * (len + 1));
		if (!line)
			err_fatal();
		line[len] = NULL;
		for (int m = 0; m < len; m++) {
			line[m] = av[i];
			i++;
		}
		if (av[i] && ((strcmp(av[i], "|")) == 0))
			a_l = 1;
		else
			a_l = 2;
		if (line[0] && (strcmp(line[0], "cd") == 0)) {
			ft_cd(line);
			continue;
		}

		pid_t	pid;
		int save0;
		int save1;
		int fd[2];
		int state;
		
		if (op) {
			save0 = dup(0);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		if (a_l = 1)
		{
			if (pipe(fd))
				err_fatal();
			
		}
	}
	return (0);
}