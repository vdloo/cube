#include <stdio.h>

#include "status.h"
#include "patterns.h"

/* compare a cube to another cube (the desired_state). 
 * -1 values in the desired cube are not checked so that
 *  partial matches can also be check (like only verify a row)
 *  returns 0 if the cube matches, otherwise how much pieces don't
 */
int count_mismatches(int cube[6][9], int desired_state[6][9])
{
     int face, piece, weight, not_matching = 0;
     for (face = 0; face < 6; face++) {
          for (piece = 0; piece < 9; piece++) {
               /* skip checking pieces we don't care about */
               if (desired_state[face][piece] == -1) {
                    continue;
               }
               if (cube[face][piece] != desired_state[face][piece]) {
		    weight = 0;
		    if (piece == 4) {
			/* when a middle piece doesn't align, count that heavier than any other piece */
			weight = weight + 10;
		    } else {
                        not_matching++;
			weight++;
		    }
	            not_matching = not_matching + weight;
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

