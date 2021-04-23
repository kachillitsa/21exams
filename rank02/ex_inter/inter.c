#include <unistd.h>

int	main(int ac, char **av)
{
	int i;
	int ascii[255];

	if (ac == 3)
	{
		i = 0;
		while (i < 255)
			ascii[i++] = 0;//заполняем "библиотеку" нулями
		i = 0;
		while (av[2][i])
		{
			if (ascii[(int)av[2][i]] == 0)
				ascii[(int)av[2][i]] = 1;
			i++;
		}
		i = 0;
		while (av[1][i])
		{
			if (ascii[(int)av[1][i]] == 1)
			{
				ascii[(int)av[1][i]] = 2;
				write (1, &av[1][i], 1);
			}
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}

/*

Assignment name  : inter
Expected files   : inter.c
Allowed functions: write

en
Write a program that takes two strings and displays, without doubles, the
characters that appear in both strings, in the order they appear in the first
one.
The display will be followed by a \n.
If the number of arguments is not 2, the program displays \n.

Examples:
./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
padinto$
./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6ewg4$
./inter "nothing" "This sentence hides nothing" | cat -e
nothig$
./inter | cat -e
$
*/