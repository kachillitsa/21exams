#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_rec
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	paint;
}				t_rec;

void	draw_rec(t_rec rec, int wid, int hei, char **field)
{
	int i = 0;
	int j;

	while(i < hei)
	{
		j = 0;
		while (j < wid)
		{
			if (j >= rec.x && j <= rec.width + rec.x && i >= rec.y && i <= rec.height + rec.y)
			{
				if (rec.type == 'R' || j < rec.x + 1 || j > rec.width + rec.x - 1 || i < rec.y + 1 || i > rec.height + rec.y - 1)
					field[i][j] = rec.paint;
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
	t_rec rec;
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
	while ((result = fscanf(file, "%c %f %f %f %f %c\n", &rec.type, &rec.x, &rec.y, &rec.width, &rec.height, &rec.paint)) != EOF)
	{
		if (result < 6 || rec.width <= 0 || rec.height <= 0 || (rec.type != 'r' && rec.type != 'R'))
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
		if (rec.type == 'r' || rec.type == 'R')
			draw_rec(rec, wid, hei, field);
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