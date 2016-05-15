#include <stdio.h>
#include <stdlib.h>

/* map colors to numbers. Western color scheme (blue-orange-yellow / minus yellow) */

const char *colors[6] = {
	/* sides */
	"white", "red", "yellow", "orange", 
	/* bottom and top */
	"green", "blue"
};


/* returns the first letter of a color specified by number */
char color2letter(int color)
{
	return colors[color][0];
}

/* in c the % operator is 'remainder', not 'modulo'. because I'm 
   trying to get the modulo with a negative number the difference 
   is visible. remainder: -1 % 4 == -1 (floor division), modulo: -1 % 4 == 3
   this function implements modulo like % in python2 and modulo in racket
*/
int mod(int a, int b)
{
	int ret;
	if (b < 0) {
		ret = mod(-a, -b);
	} else {
		ret = a % b;
		if (ret < 0) {
			ret += b;
		}
	}	
	return ret;
}


/* prints a 3d view of the cube, shows 3 sides */
void print_cube(int cube[6][9])
{
	/* loop over the cube and translate the colors to letters for the visible 3 faces */
	char faces[6][9], letter;
	int face, piece, color;
	for (face = 0; face < 6; face++) {
		for (piece = 0; piece < 9; piece++) {
			color = cube[face][piece];
			letter = color2letter(color);
			faces[face][piece] = letter;
			}
	}

	/* print the cube, front view and 90 deg tilted right view. 
	   shows 5 sides of the cube */
	printf("    +%c-%c-%c---+ ",       faces[5][6], faces[5][7], faces[5][8]);
	printf("    +%c-%c-%c---+ \n",     faces[5][2], faces[5][1], faces[5][0]);
	printf("   / %c %c %c  /| ",       faces[5][3], faces[5][4], faces[5][5]);
	printf("   / %c %c %c  /| \n",     faces[5][5], faces[5][4], faces[5][3]);
	printf("  /  %c %c %c / | ",       faces[5][0], faces[5][1], faces[5][2]);
	printf("  /  %c %c %c / | \n",     faces[5][8], faces[5][7], faces[5][6]);
	printf(" +--------+%c%c%c ",       faces[1][6], faces[1][7], faces[1][8]);
	printf(" +--------+%c%c%c \n",     faces[3][6], faces[3][7], faces[3][8]);
	printf(" |        |%c%c%c ",       faces[1][3], faces[1][4], faces[1][5]);
	printf(" |        |%c%c%c \n",     faces[3][3], faces[3][4], faces[3][5]);
	printf(" |%c  %c  %c |%c%c%c ",    faces[0][6], faces[0][7], faces[0][8], 
					   faces[1][0], faces[1][1], faces[1][2]);
	printf(" |%c  %c  %c |%c%c%c \n",  faces[2][6], faces[2][7], faces[2][8], 
					   faces[3][0], faces[3][1], faces[3][2]);
	printf(" |%c  %c  %c | /  ",       faces[0][3], faces[0][4], faces[0][5]);
	printf(" |%c  %c  %c | /  \n",     faces[2][3], faces[2][4], faces[2][5]);
	printf(" |%c  %c  %c |/   ",       faces[0][0], faces[0][1], faces[0][2]);
	printf(" |%c  %c  %c |/   \n",     faces[2][0], faces[2][1], faces[2][2]);
	printf(" +--------+    ");
	printf(" +--------+    \n");
}

/* translate the rotation translation to a vertical movement */
int translate_vertical(int face)
{
	/* 0 is the white face */
	/* 5 is the top face */
	/* 2 is the yellow face */
	/* 4 is the bottom face */
	if (face == 1) {
		return 5;
	} else if (face == 3) {
		return 4;
	} else {
		return face;
	}
}

/* for a vertical swap the orientation of the piece has to be changed 
   for example: the bottom left piece of the top face is no longer the bottom
   left piece when swapped with the back face (yellow from the white face 
   perspective), it then has become the top right piece */
int translate_piece(int swap_face, int next_face, int piece)
{
	if (swap_face == 5 && next_face == 2) {
		/* swapping the top with the back (rotate up) */
		return 8 - piece;
	} else if (swap_face == 2 && next_face == 5) {
		/* swapping the back with the top (rotate down) */
		return 8 - piece;
	} else if (swap_face == 2 && next_face == 4) {
		/* swapping the back with the bottom (rotate up) */
		return 8 - piece;
	} else if (swap_face == 4 && next_face == 2) {
		/* swapping the bottom with the back (rotate down) */
		return 8 - piece;
	} else {
		/* not doing a vertical translation that requires an orientation change */
		return piece;
	}
}

const int left_surface_rotate_mapping[9] = {
	/* bottom layer */
	6, 3, 0,
	/* middle layer */
	7, 4, 1,
	/* top layer */
	8, 5, 2
};

const int right_surface_rotate_mapping[9] = {
	/* bottom layer */
	2, 5, 8,
	/* middle layer */
	1, 4, 7,
	/* top layer */
	0, 3, 6
};

/* rotate the surface of a face 90 degrees 
   direction == 0 -> left rotate:
   6 7 8  0 3 6
   3 4 5  1 4 7
   0 1 2  2 5 8

   direction == 1 -> right rotate:
   8 5 2  6 7 8 
   7 4 1  3 4 5
   6 3 0  0 1 2 
*/

void rotate_surface(int cube[6][9], int face, int direction)
{
	int piece, new_piece;
	int tmp_face[9];

	for (piece = 0; piece < 9; piece++) {
		if (direction == 0) {
		    if (face > 3 ) {
		        /* rotate the other way on top an bottom (inverted faces) */
		        new_piece = right_surface_rotate_mapping[piece];
		    } else {
		        new_piece = left_surface_rotate_mapping[piece];
		    }
		} else if(direction == 1) {
		    if (face > 3 ) {
		        /* rotate the other way on top an bottom (inverted faces) */
		        new_piece = left_surface_rotate_mapping[piece];
		    } else {
		        new_piece = right_surface_rotate_mapping[piece];
		    }
		} 
		tmp_face[piece] = cube[face][new_piece];
	}
	for (piece = 0; piece < 9; piece++) {
		cube[face][piece] = tmp_face[piece];
	}
}

/* rotate one of the 3 layers. bottom layer is 0, 
   top layer is 2 for left/right, left layer 
   is 0, right layer is 2 for up/down. 

   direction 0 is left, 1 is right, 2 is down, 3 is up
*/
void rotate(int cube[6][9], int layer, int direction)
{
	/* loop over three sides of the cube (not four!) for the face that was specified */
	int face, piece, next_piece, swap_face, next_face, 
		initial_piece, piece_increment, max_piece;

	/* if we are rotating horizontally, the initial piece is the product of layer and 3.
	   if we are rotating vertically, the initial piece is the layer but the next 
	   piece is the current piece plus 3 (because we go up a layer in the face). */
	if (direction < 2) {
		initial_piece = layer * 3;
		piece_increment = 1;
	} else {
		initial_piece = layer;
		piece_increment = 3;
	}

	for (face = 0; face < 3; face++) {
		/* get the next face to swap with, pick the right face if direction 0 
		   (rotate left), the left face if direction 1 (rotate right), the up
		   face if direction 3 (rotate down), the down face if direction 3 
		   (rotate up) */
		if (mod(direction, 2) == 0) {
			swap_face = face;
			next_face = mod(swap_face + 1, 4);
		} else {
			swap_face = 3 - face;
			next_face = mod(swap_face - 1, 4);
		}

		/* if we are rotating up or down instead of left or right, we
		   need to translate the movement to vertical instead of horizontal */
		if (direction > 1) {
			next_face = translate_vertical(next_face);
			swap_face = translate_vertical(swap_face);
		}


		/* for every piece on the layer of the face that was specified,
		   bitwise XOR three times to swap the values. this way we swap the
		   value of piece x on face A with B, B with C and C with D etc. 
		   XOR swap: https://en.wikipedia.org/wiki/XOR_swap_algorithm
		   note: a temp var is faster on modern CPUs but this is just cool
		*/
		max_piece = initial_piece + (3 * piece_increment);
		for (piece = initial_piece; piece < max_piece; piece = piece + piece_increment) {
			next_piece = translate_piece(swap_face, next_face, piece);
			cube[swap_face][piece] = cube[swap_face][piece] ^ cube[next_face][next_piece];
			cube[next_face][next_piece] = cube[swap_face][piece] ^ cube[next_face][next_piece];
			cube[swap_face][piece] = cube[swap_face][piece] ^ cube[next_face][next_piece];
		}
		
	}
	/* if a side layer is rotated, also rotate the surface */
	if (layer == 0) {
		switch(direction) {
			case 0:
				/* rotate face 4 (bottom) left */
				rotate_surface(cube, 4, 0);
				break;
			case 1:
				/* rotate face 4 (bottom) right */
				rotate_surface(cube, 4, 1);
				break;
			case 2:
				/* rotate face 3 (left) left */
				rotate_surface(cube, 3, 0);
				break;
			case 3:
				/* rotate face 3 (left) right */
				rotate_surface(cube, 3, 1);
				break;
		}
	} else if (layer == 2) {
		switch(direction) {
			case 0:
				/* rotate face 5 (top) left */
				rotate_surface(cube, 5, 0);
				break;
			case 1:
				/* rotate face 5 (top) right */
				rotate_surface(cube, 5, 1);
				break;
			case 2:
				/* rotate face 1 (right) left */
				rotate_surface(cube, 1, 0);
				break;
			case 3:
				/* rotate face 1 (right) right */
				rotate_surface(cube, 1, 1);
				break;
		}
	}
}

/* rotate one of the 3 layers to the left 
   bottom layer is 0, top layer is 2 */
void rotate_left(int cube[6][9], int layer)
{
	rotate(cube, layer, 0);
}

/* rotate one of the 3 layers to the right 
   bottom layer is 0, top layer is 2 */
void rotate_right(int cube[6][9], int layer)
{
	rotate(cube, layer, 1);
}

/* rotate one of the 3 layers downwards 
   left layer is 0, right layer is 2 */
void rotate_down(int cube[6][9], int layer)
{
	rotate(cube, layer, 2);
}

/* rotate one of the 3 layers upwards 
   left layer is 0, right layer is 2 */
void rotate_up(int cube[6][9], int layer)
{
	rotate(cube, layer, 3);
}

/* the solved cube looks like this */
int solved_cube[6][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	{2, 2, 2, 2, 2, 2, 2, 2, 2},
	{3, 3, 3, 3, 3, 3, 3, 3, 3},
	{4, 4, 4, 4, 4, 4, 4, 4, 4},
	{5, 5, 5, 5, 5, 5, 5, 5, 5}
};

/* reset cube */
void reset_cube(int cube[6][9]) 
{
	int face, piece;
	for (face = 0; face < 6; face++) {
		for (piece = 0; piece < 9; piece++) {
			cube[face][piece] = solved_cube[face][piece];
		}
	}
}


void random_rotation(int cube[6][9])
{
	int random_rotation, random_layer;
		random_rotation = rand() % 4;
		random_layer = rand() % 3;
		switch(random_rotation) {
			case 0:
				rotate_left(cube, random_layer);
				break;
			case 1:
				rotate_right(cube, random_layer);
				break;
			case 2:
				rotate_down(cube, random_layer);
				break;
			case 3:
				rotate_up(cube, random_layer);
				break;
		}
}

/* put the cube in a random state (50 pseudo-random rotations) */
void shuffle_cube(int cube[6][9])
{
	int i;
	for (i = 0; i < 50; i++) {
		random_rotation(cube);
	}
}

/* check if the cube is solved, returns 1 when it is not solved, 0 when it is */
int check_solved(int cube[6][9])
{
	int face, piece, success;
	for (face = 0; face < 6; face++) {
		for (piece = 0; piece < 9; piece++) {
			if (cube[face][piece] != solved_cube[face][piece]) {
				return 1;
			}
		}
	}
	return 0;
}

void print_cube_solved_status(int cube[6][9])
{
	if (check_solved(cube) == 0) { 
		printf("cube is solved!\n");
	}
	else {
		printf("cube is not solved :(\n");
	}
}

/* randomly try rotations. with 6***(6*8) combinations this is never going to finish */
void bogosolve(int cube[6][9])
{
	printf("starting bogosolve\n");
	int i;
	for (i = 0; i < 1000000000000000; i++) {
		random_rotation(cube);
		if (check_solved(cube) == 0) { 
			/* never gonna happen */
			printf("done!");
			break;
		}
		if (i % 1000000 == 0) {
			printf("tried %d rotations\n", i);
			print_cube(cube);
			print_cube_solved_status(cube);
		}
	}
}

/* create the new cube and shuffle it */
void instantiate_cube(int cube[6][9])
{
	reset_cube(cube);
	printf("start cube looks like:\n");
	print_cube(cube);
	print_cube_solved_status(cube);

	printf("shuffling cube\n");
	shuffle_cube(cube);
	print_cube(cube);
	print_cube_solved_status(cube);
}

int main (int argc, char** argv)
{
	/* not very random but that's ok */
	srand(time(NULL));

	/* the cube consists of 6 faces, each with 9 pieces
	   the pieces go from 0 (bottom left) to 9 (top right)
	   top face piece 0 is the corner of the white face piece 6
	   top face piece 9 is the corner of yellow face piece 3
	   bottom face piece 0 is the corner of yellow face piece 6
	   bottom face piece 9 is the corner of white face piece 9 */
	int cube[6][9];
	instantiate_cube(cube);

	bogosolve(cube);

	return 0;
}
