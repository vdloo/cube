#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "mechanics.h"
#include "rotations.h"
#include "representation.h"
#include "operations.h"
#include "status.h"

int look_at_depth(int cube[6][9], int desired_state[6][9], int depth, int history[])
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
	for (move = 0; move < ALL_ROTATIONS; move++) {
	    copy_cube(test_cube, cube);
	    history[depth - 1] = move;
	    perform_signmaster_rotation(test_cube, signmaster_rotations[move]);
	    if (look_at_depth(test_cube, desired_state, depth - 1, history) == 0) {
               return 0; 
	    }
	}
    }
    return 1;
}

int iterative_deepening(int cube[6][9], int destination_cube[6][9], int max_depth)
{
     int depth = 1;

     int history[max_depth], i;
     for (i = 0; i < max_depth; i++) {
         history[i] = -1;
     }

     while (look_at_depth(cube, destination_cube, depth, history) != 0) {
         if (depth >= max_depth) {
	     printf("Not allowed to look further than %d moves. Did not find a solution.\n", max_depth);
             return 1;
         }
         depth++;
	 printf("checking %d levels deep\n", depth);
     }

     printf("Found a solution, path is: ");
     int move;
     for (i = max_depth; i > 0; i--) {
         move = history[i - 1]; 
	 if (move != -1) {
             printf("%s", signmaster_rotations[move]);
	 }
     }
     printf("\n");
     return 0;
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

     printf("\nperforming DLFUR'MEL'\n");
     perform_signmaster_rotation(cube, "DLFUR'MEL'");
     print_cube(cube);
     print_cube_solved_status(cube);

     printf("Finding a solution\n");
     iterative_deepening(cube, solved_cube, 8);

     exit(EXIT_SUCCESS);
}

