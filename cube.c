#include <stdio.h>
#include <stdlib.h>

/* map colors to numbers. Western color scheme (blue-orange-yellow / minus yellow) */

const char *colors[6] = {
	/* sides */
	"white", "red", "yellow", "orange", 
	/* bottom and top */
	"green", "blue"
};

/* all implemented individual rotations */
char *signmaster_rotations[9] = {"U", "L", "M", "S", "F", "R", "B", "D", "E"};

/* returns the first letter of a color specified by number */
char color2letter(int color)
{
	return colors[color][0];
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
			if (color == -1) {
				letter = '*';
			} else {
				letter = color2letter(color);
			}
			faces[face][piece] = letter;
			}
	}

	/* print the cube, front view and 180 deg tilted right view. 
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

	/* print the upside down cube, front view and 180 deg tilted right view. 
	   shows 5 sides of the cube */
	printf("    +%c-%c-%c---+ \n",       faces[4][6], faces[4][7], faces[4][8]);
	printf("   / %c %c %c  /| \n",       faces[4][3], faces[4][4], faces[4][5]);
	printf("  /  %c %c %c / | \n",       faces[4][0], faces[4][1], faces[4][2]);
	printf(" +--------+%c%c%c \n",       faces[3][2], faces[3][1], faces[3][0]);
	printf(" |        |%c%c%c \n",       faces[3][5], faces[3][4], faces[3][3]);
	printf(" |%c  %c  %c |%c%c%c \n",    faces[0][2], faces[0][1], faces[0][0], faces[3][8], faces[3][7], faces[3][6]);
	printf(" |%c  %c  %c | /  \n",       faces[0][5], faces[0][4], faces[0][3]);
	printf(" |%c  %c  %c |/   \n",       faces[0][8], faces[0][7], faces[0][6]);
	printf(" +--------+    \n");
}

void rotate_surface2(int cube[6][9], int surface, int clockwise)
{
	/* bottom left, middle and right */
	char temp_b_l = cube[surface][0];
	char temp_b_m = cube[surface][1];
	char temp_b_r = cube[surface][2];

	/* middle left and right */
	char temp_m_l = cube[surface][3];
	char temp_m_r = cube[surface][5];

	/* top left, middle and right */
	char temp_t_l = cube[surface][6];
	char temp_t_m = cube[surface][7];
	char temp_t_r = cube[surface][8];

	if (clockwise) {
	/* rotate to the right
	   6 7 8    0 3 6
	   3 4 5 -> 1 4 7
	   0 1 2    2 5 8 */
		cube[surface][0] = temp_b_r;
		cube[surface][1] = temp_m_r;
		cube[surface][2] = temp_t_r;

		cube[surface][3] = temp_b_m;
		cube[surface][5] = temp_t_m;

		cube[surface][6] = temp_b_l;
		cube[surface][7] = temp_m_l;
		cube[surface][8] = temp_t_l;

	} else {
	/* rotate to the left
	   6 7 8    8 5 2
	   3 4 5 -> 7 4 1
	   0 1 2    6 3 0 */
		cube[surface][0] = temp_t_l;
		cube[surface][1] = temp_m_l;
		cube[surface][2] = temp_b_l;

		cube[surface][3] = temp_t_m;
		cube[surface][5] = temp_b_m;

		cube[surface][6] = temp_t_r;
		cube[surface][7] = temp_m_r;
		cube[surface][8] = temp_b_r;
	}
}

void rotate_left_right(int cube[6][9], int layer, int clockwise)
{
	/* comments assume 
	 * rotation U:  rotate_left_right(cube, 2, 0) 
	 * and reverse
	 * rotation U': rotate_left_right(cube, 2, 1)  */
	int layer_padding = layer * 3;

	/* front top left, middle and right */
	char temp_f_l = cube[0][layer_padding];
	char temp_f_m = cube[0][layer_padding + 1];
	char temp_f_r = cube[0][layer_padding + 2];

	/* right top left, middle and right */
	char temp_r_l = cube[1][layer_padding];
	char temp_r_m = cube[1][layer_padding + 1];
	char temp_r_r = cube[1][layer_padding + 2];

	/* back top left, middle and right */
	char temp_b_l = cube[2][layer_padding];
	char temp_b_m = cube[2][layer_padding + 1];
	char temp_b_r = cube[2][layer_padding + 2];

	/* left top left, middle and right */
	char temp_l_l = cube[3][layer_padding];
	char temp_l_m = cube[3][layer_padding + 1];
	char temp_l_r = cube[3][layer_padding + 2];

	if (clockwise) {
		/* put right top row on front top row */
		cube[0][layer_padding]     = temp_l_l;
		cube[0][layer_padding + 1] = temp_l_m;
		cube[0][layer_padding + 2] = temp_l_r;

		/* put back top row on right top row */
		cube[1][layer_padding]     = temp_f_l;
		cube[1][layer_padding + 1] = temp_f_m;
		cube[1][layer_padding + 2] = temp_f_r;

		/* put left top row on back top row */
		cube[2][layer_padding]     = temp_r_l;
		cube[2][layer_padding + 1] = temp_r_m;
		cube[2][layer_padding + 2] = temp_r_r;

		/* put front top row on left top row */
		cube[3][layer_padding]     = temp_b_l;
		cube[3][layer_padding + 1] = temp_b_m;
		cube[3][layer_padding + 2] = temp_b_r;
	} else {
		/* put right top row on front top row */
		cube[0][layer_padding]     = temp_r_l;
		cube[0][layer_padding + 1] = temp_r_m;
		cube[0][layer_padding + 2] = temp_r_r;

		/* put back top row on right top row */
		cube[1][layer_padding]     = temp_b_l;
		cube[1][layer_padding + 1] = temp_b_m;
		cube[1][layer_padding + 2] = temp_b_r;

		/* put left top row on back top row */
		cube[2][layer_padding]     = temp_l_l;
		cube[2][layer_padding + 1] = temp_l_m;
		cube[2][layer_padding + 2] = temp_l_r;

		/* put front top row on left top row */
		cube[3][layer_padding]     = temp_f_l;
		cube[3][layer_padding + 1] = temp_f_m;
		cube[3][layer_padding + 2] = temp_f_r;
	}
}

void rotate_up_down(int cube[6][9], int layer, int clockwise)
{
	/* comments assume 
	 * rotation R:  rotate_up_down(cube, 2, 1) 
	 * and reverse
	 * rotation R': rotate_up_down(cube, 2, 0)  */
	int layer_padding = layer;

	/* front right bottom, middle and top */
	char temp_f_b = cube[0][layer_padding];
	char temp_f_m = cube[0][layer_padding + 3];
	char temp_f_t = cube[0][layer_padding + 6];

	/* top right bottom, middle and top */
	char temp_t_b = cube[5][layer_padding];
	char temp_t_m = cube[5][layer_padding + 3];
	char temp_t_t = cube[5][layer_padding + 6];

	/* back right (left) bottom, middle and top
	 * The orientation changes here so we need to substract
	 * the piece number from 8 so we get the inverted piece */
	char temp_b_b = cube[2][8 - layer_padding];
	char temp_b_m = cube[2][8 - (layer_padding + 3)];
	char temp_b_t = cube[2][8 - (layer_padding + 6)];

	/* bottom right (left) bottom, middle and top */
	char temp_o_b = cube[4][8 - layer_padding];
	char temp_o_m = cube[4][8 - (layer_padding + 3)];
	char temp_o_t = cube[4][8 - (layer_padding + 6)];

	if (clockwise) {
		/* put bottom right row on front right row */
		cube[0][layer_padding]     = temp_o_b;
		cube[0][layer_padding + 3] = temp_o_m;
		cube[0][layer_padding + 6] = temp_o_t;

		/* put front right row on top right row */
		cube[5][layer_padding]     = temp_f_b;
		cube[5][layer_padding + 3] = temp_f_m;
		cube[5][layer_padding + 6] = temp_f_t;

		/* put top right row on back right row */
		cube[2][8 - layer_padding]       = temp_t_b;
		cube[2][8 - (layer_padding + 3)] = temp_t_m;
		cube[2][8 - (layer_padding + 6)] = temp_t_t;

		/* put back right row on bottom right row */
		cube[4][8 - layer_padding]       = temp_b_b;
		cube[4][8 - (layer_padding + 3)] = temp_b_m;
		cube[4][8 - (layer_padding + 6)] = temp_b_t;
	} else {
		/* put top right row on front right row */
		cube[0][layer_padding]     = temp_t_b;
		cube[0][layer_padding + 3] = temp_t_m;
		cube[0][layer_padding + 6] = temp_t_t;

		/* put back right row on top right row */
		cube[5][layer_padding]     = temp_b_b;
		cube[5][layer_padding + 3] = temp_b_m;
		cube[5][layer_padding + 6] = temp_b_t;

		/* put bottom right row on back right row */
		cube[2][8 - layer_padding]       = temp_o_b;
		cube[2][8 - (layer_padding + 3)] = temp_o_m;
		cube[2][8 - (layer_padding + 6)] = temp_o_t;

		/* put front right row on bottom right row */
		cube[4][8 - layer_padding]       = temp_f_b;
		cube[4][8 - (layer_padding + 3)] = temp_f_m;
		cube[4][8 - (layer_padding + 6)] = temp_f_t;
	}
}

void perform_u_normal(int cube[6][9])
{

    rotate_left_right(cube, 2, 0);
    rotate_surface2(cube, 5, 1);
}

void perform_u_reverse(int cube[6][9])
{
    rotate_left_right(cube, 2, 1);
    rotate_surface2(cube, 5, 0);
}

void perform_d_normal(int cube[6][9])
{
    rotate_left_right(cube, 0, 1);
    rotate_surface2(cube, 4, 1);
}

void perform_d_reverse(int cube[6][9])
{
    rotate_left_right(cube, 0, 0);
    rotate_surface2(cube, 4, 0);
}

void perform_e_normal(int cube[6][9])
{
    rotate_left_right(cube, 1, 1);
}

void perform_e_reverse(int cube[6][9])
{
    rotate_left_right(cube, 1, 0);
}

void perform_r_normal(int cube[6][9])
{
    rotate_up_down(cube, 2, 1);
    rotate_surface2(cube, 1, 1);
}

void perform_r_reverse(int cube[6][9])
{
    rotate_up_down(cube, 2, 0);
    rotate_surface2(cube, 1, 0);
}

void perform_l_normal(int cube[6][9])
{
    rotate_up_down(cube, 0, 0);
    rotate_surface2(cube, 3, 1);
}

void perform_l_reverse(int cube[6][9])
{
    rotate_up_down(cube, 0, 1);
    rotate_surface2(cube, 3, 0);
}

void perform_m_normal(int cube[6][9])
{
    rotate_up_down(cube, 1, 0);
}

void perform_m_reverse(int cube[6][9])
{
    rotate_up_down(cube, 1, 1);
}


/* prototype for rotation because we do mutual recursion between perform_signmaster_rotation and rotation
 * and we need to be able to call it in perform_signmaster_rotation before defining it */
void rotation(int cube[6][9], char signmaster_letter, int reverse);

void perform_signmaster_rotation(int cube[6][9], const char *signmaster_sequence)
{
	int i, next_is_quote, cur_is_quote;

	/* Loop over chars in the str until we hit the NULL terminator */
	for (i = 0; *signmaster_sequence != '\0'; signmaster_sequence++) {
		next_is_quote = *(signmaster_sequence + 1) == '\'';
		cur_is_quote = *signmaster_sequence == '\'';

		if (cur_is_quote && next_is_quote) {
			fprintf(stderr, "Signmaster sequence contains two consecutive apostrophes! Aborting..\n");
			exit(EXIT_FAILURE);
		}

		if (cur_is_quote) {
			// do reverse rotation of previous 
			rotation(cube, *(signmaster_sequence - 1), 1);
		} else if (!next_is_quote){
			// do normal rotation of the current
			rotation(cube, *signmaster_sequence, 0);
		}
	}
}

void rotation(int cube[6][9], char signmaster_letter, int reverse)
{
	/* For the beginner's method you just have to know the simple 
	   F (front), B (back), R (right), L (left), D (down), U (up), 
	   so for now let's only implement those.
	   see: https://ruwix.com/the-rubiks-cube/notation/ */
	switch(signmaster_letter) {
		case 'U':
			if (reverse) {
				perform_u_reverse(cube);
			} else {
				perform_u_normal(cube);
			}
			break;
		case 'L':
			if (reverse) {
				perform_l_reverse(cube);
			} else {
				perform_l_normal(cube);
			}
			break;
		case 'M':
			if (reverse) {
				perform_m_reverse(cube);
			} else {
				perform_m_normal(cube);
			}
			break;
		case 'S':
			// flip cube 90 deg to the left
			perform_signmaster_rotation(cube, "UE'D'");
			if (reverse) {
				// move up middle slice
				perform_signmaster_rotation(cube, "M'");
			} else {
				// move down middle slice
				perform_signmaster_rotation(cube, "M");
			}
			// flip cube back 90 deg to the left
			perform_signmaster_rotation(cube, "U'ED");
			break;
		case 'F':
			// flip cube 90 deg to the left
			perform_signmaster_rotation(cube, "UE'D'");
			if (reverse) {
				// move up left slice
				perform_signmaster_rotation(cube, "L'");
			} else {
				// move down left slice
				perform_signmaster_rotation(cube, "L");
			}
			// flip cube back 90 deg to the left
			perform_signmaster_rotation(cube, "U'ED");
			break;
		case 'R':
			if (reverse) {
				perform_r_reverse(cube);
			} else {
				perform_r_normal(cube);
			}
			break;
		case 'B':
			perform_signmaster_rotation(cube, "UE'D'");
			if (reverse) {
				// move up right slice
				perform_signmaster_rotation(cube, "R'");
			} else {
				// move down right slice
				perform_signmaster_rotation(cube, "R");
			}
			perform_signmaster_rotation(cube, "U'ED");
			break;
		case 'D':
			if (reverse) {
				perform_d_reverse(cube);
			} else {
				perform_d_normal(cube);
			}
			break;
		case 'E':
			if (reverse) {
				perform_e_reverse(cube);
			} else {
				perform_e_normal(cube);
			}
			break;
		default:
			fprintf(stderr, "Signmaster rotation %c is not implemented! Aborting..\n", signmaster_letter);
			exit(EXIT_FAILURE);
	}
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

/* copy cube */
void copy_cube(int destination_cube[6][9], int source_cube[6][9])
{
	int face, piece;
	for (face = 0; face < 6; face++) {
		for (piece = 0; piece < 9; piece++) {
			destination_cube[face][piece] = source_cube[face][piece];
		}
	}
}

/* reset cube */
void reset_cube(int cube[6][9]) 
{
	copy_cube(cube, solved_cube);
}

void random_rotation(int cube[6][9])
{
	int random_rotation, random_layer;
		random_rotation = rand() % 11;
		switch(random_rotation) {
			case 0:
				perform_u_normal(cube);
				break;
			case 1:
				perform_u_reverse(cube);
				break;
			case 2:
				perform_m_normal(cube);
				break;
			case 3:
				perform_m_reverse(cube);
				break;
			case 4:
				perform_d_normal(cube);
				break;
			case 5:
				perform_d_reverse(cube);
				break;
			case 6:
				perform_e_normal(cube);
				break;
			case 7:
				perform_e_reverse(cube);
				break;
			case 8:
				perform_r_normal(cube);
				break;
			case 9:
				perform_r_reverse(cube);
				break;
			case 10:
				perform_l_normal(cube);
				break;
			case 11:
				perform_l_reverse(cube);
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

/* compare a cube to another cube (the desired_state). 
 * -1 values in the desired cube are not checked so that
 *  partial matches can also be check (like only verify a row)
 *  returns 0 if the cube matches, otherwise how much pieces don't
 */
int count_mismatches(int cube[6][9], int desired_state[6][9])
{
	int face, piece, success, not_matching = 0;
	for (face = 0; face < 6; face++) {
		for (piece = 0; piece < 9; piece++) {
			/* skip checking pieces we don't care about */
			if (desired_state[face][piece] == -1) {
				continue;
			}
			if (cube[face][piece] != desired_state[face][piece]) {
				not_matching++;
			}
		}
	}
	return not_matching;
}

/* check if the cube is solved, returns 1 when it is not solved, 0 when it is */
int check_solved(int cube[6][9])
{
	return count_mismatches(cube, solved_cube);
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

/* create the new cube and shuffle it */
void instantiate_cube(int cube[6][9])
{
	reset_cube(cube);
	printf("start cube looks like:\n");
	print_cube(cube);
	print_cube_solved_status(cube);

	print_cube(cube);
	print_cube_solved_status(cube);
}

int main (int argc, char** argv)
{
	/* not very random but that's ok */
	srand(getpid());

	/* the cube consists of 6 faces, each with 9 pieces
	   the pieces go from 0 (bottom left) to 9 (top right)
	   top face piece 0 is the corner of the white face piece 6
	   top face piece 9 is the corner of yellow face piece 3
	   bottom face piece 0 is the corner of yellow face piece 6
	   bottom face piece 9 is the corner of white face piece 9 */
	int cube[6][9];
	instantiate_cube(cube);

	printf("performing superflip\n");
        perform_signmaster_rotation(cube, "URRFBRBBRUULBBRU'D'RRFR'LBBUUFF");
	print_cube(cube);
	print_cube_solved_status(cube);

	printf("performing superflip\n");
        perform_signmaster_rotation(cube, "URRFBRBBRUULBBRU'D'RRFR'LBBUUFF");
	print_cube(cube);
	print_cube_solved_status(cube);

	exit(EXIT_SUCCESS);
}
