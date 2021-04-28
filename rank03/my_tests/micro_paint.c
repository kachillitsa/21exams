/*
Assignment name  : micro_paint
Expected files   : *.c *.h
Allowed functions: fopen, fread, fscanf, fclose, write, malloc, calloc, realloc, free, memset, powf, sqrtf
--------------------------------------------------------------------------------------

Write a program that will read an "operation file" and print the result in the terminal

Your program must take one argument, it will be the path to the "operation file"
If 0 or more than 1 argument is given to your program write "Error: argument" followed by a \n in STDOUT

$> ./micro_paint | cat -e
Error: argument$
$> ./micro_paint do not fear mathematics | cat -e
Error: argument$
$> 

If any problem occurs while you open and/or read the "operation file" write "Error: Operation file corrupted" followed by a \n in STDOUT

The "operation file" will contains lines with one operation per line
If a line is incorrect an error occurs.
If an error has occured your program must return 1
If no error has occured it must return 0
The last line can be with or without a \n
The lines must be read in order and therefore operations must be executed in the same order
There must be at least one space between each variable in a line

WIDTH HEIGHT BACKGROUND_CHAR
This line is always the first line of the file and it defines the zone where to draw. Your program should not display anything outside 
the draw zone. It must be there only once.
- WIDTH: must be a int with 0 < WIDTH <= 300, the horizontal number of characters to use for the draw zone
- HEIGHT: must be a int with 0 < HEIGHT <= 300, the vertical number of characters to use for the draw zone 
- BACKGROUND_CHAR: any empty space will be filled with BACKGROUND_CHAR

r X Y WIDTH HEIGHT CHAR
This operation will draw an empty rectangle, where only the border of the rectangle is drawn
- r: the character r
- X: any float, the horizontal position of the top left corner of the rectangle
- Y: any float, the vertical position of the top left corner of the rectangle
- WIDTH: a positive float but not 0, the width of the rectangle (horizontal)
- HEIGHT: a positive float but not 0, the height of the rectangle (vertical)
- CHAR: the char use to draw the rectangle

R X Y WIDTH HEIGHT CHAR
This operation will draw a filled rectangle
- R: the character R
- X: any float, the horizontal position of the top left corner of the rectangle
- Y: any float, the vertical position of the top left corner of the rectangle
- WIDTH: a positive float but not 0, the width of the rectangle (horizontal)
- HEIGHT: a positive float but not 0, the height of the rectangle (vertical)
- CHAR: the char use to draw the rectangle

The draw zone is divided in rectangles that can contain one character each (because we are in a terminal...), we will call them pixel
To make everything easier, we will use only the top left corner of the pixel to know if that pixel is in a rectangle or not
A pixel with a top left corner with a distance bigger or equal than 1 from the border of a rectangle is not part of an empty rectangle 
A pixel with a top left corner with a distance lower than 1 from the border of a rectangle is part of an empty rectangle.

You should look at the image while reading the next few lines. It represents a terminal. We've set a draw zone of WIDTH 5 and HEIGHT 3.
We've wrote different character to help you understand the following explanations.
- If you want to draw the operation: r 2.5 1.5 1 1 X (the green rectangle)
-- it means that the character 'D' in the image will be replaced by 'X' 

You should find our_micro_paint to help you test yours with some operation_file.example

Hint:
If a point is defined as (Xa, Ya)
And a rectangle with a top left corner (Xtl, Ytl) and a bottom right corner (Xbr, Ybr)
If Xtl <= Xa <= Xbr and Ytl <= Ya <= Ybr then the point is in the rectangle
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_sq
{
	char		s_r;
	float		s_x;
	float		s_y;
	float		s_wi;
	float		s_he;
	char		s_c;
}				t_sq;

void	draw_sq(t_sq sq, int wi, int he, char **list)
{
	int i = 0;
	int j;

	while(i < he)
	{
		j = 0;
		while (j < wi)
		{
			if (j >= sq.s_x && j <= sq.s_wi + sq.s_x && i >= sq.s_y && i <= sq.s_he + sq.s_y)
			{
				if (sq.s_r == 'R' || j < sq.s_x + 1 || j > sq.s_wi + sq.s_x - 1 || i < sq.s_y + 1 || i > sq.s_he + sq.s_y - 1)
					list[i][j] = sq.s_c;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	FILE *file;
	t_sq	sq;
	int wi;
	int he;
	char bg_c;
	int res;
	char **list;
	int i;

	i = 0;
	if (ac != 2)
	{
		write (1, "Error: argument\n", 17);
		return (1);
	}
	if ((file = fopen(av[1], "r")) == NULL)
	{
		write (1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	res = fscanf(file, "%d %d %c\n", &wi, &he, &bg_c);
	if (res < 3 || wi > 300 || wi < 1 || he > 300 || he < 1)
	{
		write (1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	list = malloc(he * sizeof(char *));
	while (i < he)
	{
		list[i] = malloc(wi);
		memset(list[i], bg_c, wi);
		i++;
	}
	while ((res = fscanf(file, "%c %f %f %f %f %c\n", sq.s_r, sq.s_x, sq.s_y, sq.s_wi, sq.s_he, sq.s_c)) != EOF)
	{
		if (res < 6 || (sq.s_r != "r" && sq.s_r != "R") || sq.s_wi <= 0 || sq.s_he <= 0)
		{
			write (1, "Error: Operation file corrupted\n", 33);
			return (1);
		}
		draw_sq(sq, wi, he, list);
	}
	i = 0;
	while (i < he)
	{
		write(1, list[i], wi);
		write(1, "\n", 1);
		i++;
	}
	fclose(file);
	return (0);
}