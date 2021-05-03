#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

void error_cd_bad_args(void)
{
	write(2, "error: cd: bad arguments\n", 25);
}

void error_cd_cannot_change(char *str)
{
	write(2, "error: cd: cannot change directory to ", 39);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void error_cannot_exec(char *str)
{
	write(2, "error: cannot execute ", 23);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void exit_fatal(void)
{
	write(2, "error: fatal\n", 14);
	exit(1);
}

void	ft_cd(char **line)
{
	if (ft_strlen(*line) != 2)
	{
		error_cd_bad_args();
		return;
	}
	if (chdir(line[1]))
		error_cd_cannot_change(line[1]);
}

int count_len(char **str, int i)
{
	int len = 0;
	while(str[i] && strcmp(str[i], ";") && strcmp(str[i], "|"))
	{
		i++;
		len++;
	}
	return len;
}

#define PIPE 1
#define NOTPIPE 2

int		main(int ac, char **av, char **env)
{
	int i = 1;
	int op = 0;
	int	len = 0;
	char **line = NULL;
	int afterline = 0;

	if (ac <= 1)
		return 0;
	while (i < ac)
	{
		if (!(strcmp(av[i], "|")) || !(strcmp(av[i], ";"))) { //!strcmp means equal returns 0
			i++;
			continue;
		}
		len = count_len(av, i);
		line = malloc(sizeof(char *) * (len + 1));
		if (!line)
			exit_fatal();
		line[len] = NULL;
		for (int m = 0; m < len; m++)
		{
			line[m] = av[i];
			i++;
		}
		if (av[i] && (strcmp(av[i], "|") == 0))
			afterline = PIPE;
		else
			afterline = NOTPIPE;
		if (!(strcmp(line[0], "cd")))
		{
			ft_cd(line);
			continue;
		}
		pid_t pid;
		int stat;
		int save0;
		int save1;
		int fd[2];
		if(op)
		{
			save0 = dup(0);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		if (afterline == PIPE)
		{
			if (pipe(fd))
				exit_fatal();
			save1 = dup(1);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		pid = fork();
		if(pid < 0) exit_fatal();
		else if (pid == 0) // baby
		{
			if(execve(line[0], line, env))
				error_cannot_exec(line[0]);
			exit(0);
		}
		else
			waitpid(pid, &stat, 0);
		if(op)
		{
			dup2(save0, 0);
			close(save0);
			op = 0;
		}
		if (afterline == PIPE)
		{
			dup2(save1, 1);
			close(save1);
			op = 1;
		}
		free(line);
	}
	return 0;
}