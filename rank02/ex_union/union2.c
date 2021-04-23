#include <unistd.h>

int main(int ac, char **av)
{
	int i = 0;
	int j = 0;
	if (ac == 3)
	{
		i = 0;
		while (av[1][i])// повторяются ли символы в первой строке
		{
			j = 0;
			while (j < i)
			{
				if (av[1][i] == av[1][j])
					break;
				j++;
			}
			if (i == j)
				write(1, &av[1][i], 1);
			i++;
		}
		i = 0;
		while (av[2][i]) // совпадают ли символы во второй
		{
			j = 0;
			while (av[1][j])
			{
				if (av[2][i] == av[1][j])
					break;
				j++;
			}
			if (av[1][j] != '\0')//	если проверка прошла правильно, j указывает на 
			//						конец первой строки. иначе переходим к следующему символу
			{
				i++;
				continue;
			}
			j = 0;
			while (j < i)
			{
				if (av[2][i] == av[2][j])
					break;
				j++;
			}
			if (i != j)
			{
				i++;
				continue;
			}
			write(1, &av[2][i], 1);
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}

/*

Assignment name  : union
Expected files   : union.c
Allowed functions: write

Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.
The display will be in the order characters appear in the command line, and
will be followed by a \n.
If the number of arguments is not 2, the program displays \n.

Example:
$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>

*/