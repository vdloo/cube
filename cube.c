#include <stdio.h>

/* map colors to numbers. Western color scheme (blue-orange-yellow / minus yellow) */

const char *colors[6] = {
	"white", "red", "blue",
	"orange", "green", "yellow"
};


/* returns the first letter of a color specified by number */
char color2letter(int color)
{
	return colors[color][0];
}


/* prints a 3d view of the cube, shows 3 sides */
void print_cube(int cube[6][9])
{
	/* loop over the cube and translate the colors to letters for the 
	   first 3 faces */
	char faces[3][9], letter;
	int face, piece, color;
	for (face = 0; face < 3; face++) {
		for (piece = 0; piece < 9; piece++) {
			color = cube[face][piece];
			letter = color2letter(color);
			faces[face][piece] = letter;
        	}
	}

	/* print the first 3 faces */
	printf("    +%c-%c-%c---+\n",     faces[2][0], faces[2][1], faces[2][2]);
	printf("   / %c %c %c  /|\n",     faces[2][3], faces[2][4], faces[2][5]);
	printf("  /  %c %c %c / |\n",     faces[2][6], faces[2][7], faces[2][8]);
	printf(" +--------+%c%c%c\n",     faces[1][0], faces[1][1], faces[1][2]);
	printf(" |        |%c%c%c\n",     faces[1][3], faces[1][4], faces[1][5]);
	printf(" |%c  %c  %c |%c%c%c\n",  faces[0][0], faces[0][1], faces[0][2], 
					  faces[1][6], faces[1][7], faces[1][8]);
	printf(" |%c  %c  %c | / \n",     faces[0][3], faces[0][4], faces[0][5]);
	printf(" |%c  %c  %c |/  \n",     faces[0][6], faces[0][7], faces[0][8]);
	printf(" +--------+   \n");
}

main ()
{
	const char *colors[6] = {
		"white", "red", "blue",
		"orange", "green", "yellow"
	};
	int cube[6][9] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{2, 2, 2, 2, 2, 2, 2, 2, 2},
		{3, 3, 3, 3, 3, 3, 3, 3, 3},
		{4, 4, 4, 4, 4, 4, 4, 4, 4},
		{5, 5, 5, 5, 5, 5, 5, 5, 5}
	};
	print_cube(cube);
}

