#include <stdio.h>
#include <stdlib.h>

#include "operations.h"
#include "representation.h"
#include "rotations.h"
#include "patterns.h"

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
     int random_rotation;
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

void instantiate_cube(int cube[6][9])
{
     reset_cube(cube);
     printf("start cube looks like:\n");
     print_cube(cube);
     print_cube_solved_status(cube);
}

/* put the cube in a random state (50 pseudo-random rotations) */
void shuffle_cube(int cube[6][9])
{
     int i;
     for (i = 0; i < 50; i++) {
          random_rotation(cube);
     }
}

