#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct s_cir
{
	char	type;
	float	x;
	float	y;
	float	rad;
	char	paint;
}				t_cir;

void	draw_cir(t_cir cir, int wid, int hei, char **field)
{
	int i = 0;
	int j;

	while(i < hei)
	{
		j = 0;
		while (j < wid)
		{
			if (sqrtf(powf((cir.x - j), 2)+ powf((cir.y - i), 2)) <= cir.rad)
			{
				if (cir.type == 'C' || sqrtf(powf((cir.x - j), 2)+ powf((cir.y - i), 2)) > cir.rad - 1)
					field[i][j] = cir.paint;
			}
			j++;
		}
		i++;
	}
}

int main(int argc, char *argv[])
{
	FILE *file;
	int wid;
	int hei;
	char ch;
	int result;
	t_cir cir;
	char **field;
	int i;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if ((file = fopen(argv[1], "r")) == NULL)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	result = fscanf(file, "%d %d %c\n", &wid, &hei, &ch);
	if (result < 3 || wid > 300 || wid <= 0 || hei > 300 || hei <= 0)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	field = malloc(hei * sizeof(char *));
	i = 0;
	while (i < hei)
	{
		field[i] = malloc(wid);
		memset(field[i], ch, wid);
		i++;
	}
	while ((result = fscanf(file, "%c %f %f %f %c\n", &cir.type, &cir.x, &cir.y, &cir.rad, &cir.paint)) != EOF)
	{
		if (result < 5 || cir.rad <= 0 || (cir.type != 'c' && cir.type != 'C'))
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
		if (cir.type == 'c' || cir.type == 'C')
			draw_cir(cir, wid, hei, field);
	}
	i = 0;
	while (i < hei)
	{
		write(1, field[i], wid);
		write(1, "\n", 1);
		i++;
	}

	fclose(file);
	return (0);
}