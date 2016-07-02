#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "mechanics.h"
#include "rotations.h"
#include "representation.h"
#include "operations.h"
#include "status.h"

int iterative_deepening(int cube[6][9], int desired_state[6][9], const char *path, int depth)
{
    int move, state;
    if (depth == 0) {
        state = count_mismatches(cube, desired_state);
	if (state == 0) {
	    printf("Found a solution!\n");
            print_cube(cube);
            print_cube_solved_status(cube);
	}
	return state;
    } else {
	int test_cube[6][9];
        char rev[2];

	for (move = 0; move < 9; move++) {
	    copy_cube(test_cube, cube);
	    perform_signmaster_rotation(test_cube, signmaster_rotations[move]);
	    if (iterative_deepening(test_cube, desired_state, path, depth - 1) == 0) {
               return 0; 
	    }
	}
	for (move = 0; move < 9; move++) {
	    copy_cube(test_cube, cube);
	    memset(rev, '\0', sizeof(rev));
	    strcpy(rev, signmaster_rotations[move]);
	    strcat(rev, "'");
	    perform_signmaster_rotation(test_cube, rev);
	    if (iterative_deepening(test_cube, desired_state, path, depth - 1) == 0) {
               return 0; 
	    }
	}
    }
    return 1;
}

int main()
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

     printf("performing R\n");
     perform_signmaster_rotation(cube, "ULURUDU");
     print_cube(cube);
     print_cube_solved_status(cube);

     printf("Finding a solution\n");

     int depth = 1;
     while (iterative_deepening(cube, solved_cube, "notyetapath", depth) != 0) {
	 printf("checking %d levels deep\n", depth);
         depth++;
     }

     exit(EXIT_SUCCESS);
}

