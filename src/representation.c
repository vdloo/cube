#include <stdio.h>

#include "representation.h"

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

     /* print the cube, front view and 180 deg rotated right view and 180 tilted rotated left. */
     printf("    front        180° ↺        180° ↶\n");
     printf("   +%c-%c-%c---+ ",       faces[5][6], faces[5][7], faces[5][8]);
     printf("   +%c-%c-%c---+ ",     faces[5][2], faces[5][1], faces[5][0]);
     printf("   +%c-%c-%c---+ \n",       faces[4][6], faces[4][7], faces[4][8]);
     printf("  / %c %c %c  /| ",       faces[5][3], faces[5][4], faces[5][5]);
     printf("  / %c %c %c  /| ",     faces[5][5], faces[5][4], faces[5][3]);
     printf("  / %c %c %c  /| \n",       faces[4][3], faces[4][4], faces[4][5]);
     printf(" /  %c %c %c / | ",       faces[5][0], faces[5][1], faces[5][2]);
     printf(" /  %c %c %c / | ",     faces[5][8], faces[5][7], faces[5][6]);
     printf(" /  %c %c %c / | \n",       faces[4][0], faces[4][1], faces[4][2]);
     printf("+--------+%c%c%c ",       faces[1][6], faces[1][7], faces[1][8]);
     printf("+--------+%c%c%c ",     faces[3][6], faces[3][7], faces[3][8]);
     printf("+--------+%c%c%c \n",       faces[3][2], faces[3][1], faces[3][0]);
     printf("|        |%c%c%c ",       faces[1][3], faces[1][4], faces[1][5]);
     printf("|        |%c%c%c ",     faces[3][3], faces[3][4], faces[3][5]);
     printf("|        |%c%c%c \n",       faces[3][5], faces[3][4], faces[3][3]);
     printf("|%c  %c  %c |%c%c%c ",    faces[0][6], faces[0][7], faces[0][8], 
                           faces[1][0], faces[1][1], faces[1][2]);
     printf("|%c  %c  %c |%c%c%c ",  faces[2][6], faces[2][7], faces[2][8], 
                           faces[3][0], faces[3][1], faces[3][2]);
     printf("|%c  %c  %c |%c%c%c \n",    faces[0][2], faces[0][1], faces[0][0], 
                           faces[3][8], faces[3][7], faces[3][6]);
     printf("|%c  %c  %c | /  ",       faces[0][3], faces[0][4], faces[0][5]);
     printf("|%c  %c  %c | /  ",     faces[2][3], faces[2][4], faces[2][5]);
     printf("|%c  %c  %c | /  \n",       faces[0][5], faces[0][4], faces[0][3]);
     printf("|%c  %c  %c |/   ",       faces[0][0], faces[0][1], faces[0][2]);
     printf("|%c  %c  %c |/   ",     faces[2][0], faces[2][1], faces[2][2]);
     printf("|%c  %c  %c |/   \n",       faces[0][8], faces[0][7], faces[0][6]);
     printf("+--------+    ");
     printf("+--------+    ");
     printf("+--------+    \n");
}

