#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "operations.h"
#include "status.h"
#include "representation.h"
#include "solver.h"

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

     shuffle_cube(cube);
     print_cube(cube);
     print_cube_solved_status(cube);

     yellow_cross_solver(cube);

     exit(EXIT_SUCCESS);
}

