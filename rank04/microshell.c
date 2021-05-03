#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

void	err_args()
{
	write(2, "error: cd: bad arguments\n", 26);
}

void	err_path(char *str)
{
	write(2, "error: cd: cannot change directory to ", 39);
	write(2, str, strlen(str));
	write(2, "\n", 1);
}

void err_exec(char *str)
{
	write(2, "error: cannot execute ", 23);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	exit_fatal(void)
{
	write(2, "error: fatal\n", 14);
	exit(1);
}

#define PIPE 1

int		count_len(char **av, int i)
{
	int len = 0;
	while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
	{
		i++;
		len++;
	}
	return(len);
}

void	ft_cd(char **line)
{
	int i = 0;
	while(line[i]) i++;
	if(i != 2)
	{
		err_args();
		return;
	}
	if (chdir(line[1]))
		err_path(line[1]);
}

int		main(int ac, char **av, char **env)
{
	// ____________________PART ONE
	int		i = 1;
	int		len = 0;
	char	**line = NULL;
	int		after_line = 0;
	int		op = 0;

	if (ac <= 1)
	{
		return(0);
	}
	while (i < ac)
	{
		if (!(strcmp(av[i], "|")) || !(strcmp(av[i], ";")))
		{
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
			after_line = PIPE;
		else
			after_line = 2;
		if (!(strcmp(line[0], "cd")))
		{
			ft_cd(line);
			continue;
		}
	// ____________________PART TWO
		pid_t pid;
		int state;
		int fd[2];
		int save0;
		int save1;

		if (op)
		{
			save0 = dup(0);
			dup2(fd[0], 0);
			close(fd[0]);
		}

		if(after_line == PIPE)
		{
			if(pipe(fd))
				exit_fatal();
			save1 = dup(1);
			dup2(fd[1], 1);
			close(fd[1]);
		}

		pid = fork();
		if (pid <0)
			exit_fatal();
		else if(pid == 0)
		{
			if(execve(line[0], line, env))
				err_exec(line[0]);
			exit(0);
		}
		else
			waitpid(pid, &state, 0);
		if(op)
		{
			dup2(save0, 0);
			close(save0);
			op = 0;
		}
		if (after_line == PIPE)
		{
			dup2(save1, 1);
			close(save1);
			op = 1;
		}
		free(line);
	}
	return(0);
}