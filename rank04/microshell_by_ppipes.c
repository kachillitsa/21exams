#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i] != '\0')
		i++;
	return i;
}

void error_cd_bad_args(void)
{
	write(2, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
}

void error_cd_cannot_change(char *str)
{
	write(2, "error: cd: cannot change directory to ", ft_strlen("error: cd: cannot change directory to "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void error_cannot_exec(char *str)
{
	write(2, "error: cannot execute ", ft_strlen("error: cannot execute "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void exit_fatal(void)
{
	write(2, "error: fatal\n", ft_strlen("error: fatal\n"));
	exit(1);
}

void ft_cd(char **line)
{
	int i = 0;
	while(line[i]) i++;
	if (i != 2)
	{
		error_cd_bad_args();
		return;
	}
	if (chdir(line[1])) //если успешно перешел вернет ноль так что заходим внутрь при неудаче
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

#define END 2
#define PIPE 1
#define SEMI 3

int main(int argc, char **argv, char **env)
{
	int i = 1;
	int len = 0;
	char **line = NULL;
	int after_line = 0;
	int opened = 0;

	if (argc > 1) // иначе ретерн
	{
		while(i < argc)
		{
			if (!(strcmp(argv[i], ";")) || !(strcmp(argv[i], "|"))) {
				i++; // пропустить
				continue;
			}
			len = count_len(argv, i); // колво аргументов в команде
			line = malloc(sizeof(char *) * (len + 1)); //будущий массив указателей на аргументы
			if (!line)
				exit_fatal();// проверили малок
			line[len] = NULL; // ограничить
			for (int m = 0; m < len; m++)
			{
				line[m] = argv[i]; //заполнили аргв
				i++;
			}
			if(!argv[i])
				after_line = END;
			if (argv[i] && (strcmp(argv[i], ";") == 0)) //если стрсмп увидит налл он сегнется!
				after_line = SEMI;
			else if (argv[i] && (strcmp(argv[i], "|") == 0))
				after_line = PIPE;
			if (!(strcmp(line[0], "cd"))) //если 1ый арг сд
			{
				ft_cd(line);
				continue; //новый цикл
			}
			
			pid_t pid;
			int status;
			int save0;
			int save1;
			int fd[2];

			if (opened) // пропускаем в первый раз 100%, зайдем если предыдущий - пайп
			{
				save0 = dup(0);
				dup2(fd[0], 0);
				close(fd[0]);
			}
			if (after_line == PIPE)
			{
				if (pipe(fd))
					exit_fatal();
				save1 = dup(1); // тут save1 мы сохранили 1
				dup2(fd[1], 1); // теперь 1 это fd[1], сам fd[1] дублирован но не нужен int dup2(int oldfd, int newfd);
				close(fd[1]); // поэтому здесь его закрываем
			}

			pid = fork();
			if (pid < 0) exit_fatal();
			else if (pid == 0) // ребенок
			{
				if (execve(line[0], line, env)) //подменяет исходный код
					error_cannot_exec(line[0]);
				exit(0);
			}
			else // родитель ждет
				waitpid(pid, &status, 0);

			if (opened)
			{
				dup2(save0, 0);
				close(save0);
				opened = 0;
			}

			if (after_line == PIPE)
			{
				dup2(save1, 1); // поставить все на место что раздолбали в 120-.. строках
				close(save1);
				opened = 1;
			}
			free(line); //каждая отдельная команда
		}
	}
	return 0;
}