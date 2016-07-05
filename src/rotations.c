#include <stdio.h>
#include <stdlib.h>

#include "mechanics.h"
#include "rotations.h"

/* all implemented individual rotations */
char *signmaster_rotations[ALL_ROTATIONS] = {
	/* face rotations and slice turns */
	"U", "U'",
	"L", "L'",
	"M", "M'",
       	"S", "S'",
       	"F", "F'",
       	"R", "R'",
       	"B", "B'",
       	"D", "D'",
       	"E", "E'",

	/* whle cube rotations */
       	"X", "X'",
	"Y", "Y'",
       	"Z", "Z'",

	"URU'R'U'F'UF",
	"U'L'ULUFU'F'",

	/* beginners method algorithms */

	"FRUR'U'F'",
	"RUR'URUUR'U",
	"URU'L'UR'U'L",
	"R'D'RD",
	"FDF'",
	"R'DDRDR'D'R",
	"R'D'R",
};

void perform_u_normal(int cube[6][9])
{

    rotate_left_right(cube, 2, 0);
    rotate_surface(cube, 5, 1);
}

void perform_u_reverse(int cube[6][9])
{
    rotate_left_right(cube, 2, 1);
    rotate_surface(cube, 5, 0);
}

void perform_d_normal(int cube[6][9])
{
    rotate_left_right(cube, 0, 1);
    rotate_surface(cube, 4, 1);
}

void perform_d_reverse(int cube[6][9])
{
    rotate_left_right(cube, 0, 0);
    rotate_surface(cube, 4, 0);
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
    rotate_surface(cube, 1, 1);
}

void perform_r_reverse(int cube[6][9])
{
    rotate_up_down(cube, 2, 0);
    rotate_surface(cube, 1, 0);
}

void perform_l_normal(int cube[6][9])
{
    rotate_up_down(cube, 0, 0);
    rotate_surface(cube, 3, 1);
}

void perform_l_reverse(int cube[6][9])
{
    rotate_up_down(cube, 0, 1);
    rotate_surface(cube, 3, 0);
}

void perform_m_normal(int cube[6][9])
{
    rotate_up_down(cube, 1, 0);
}

void perform_m_reverse(int cube[6][9])
{
    rotate_up_down(cube, 1, 1);
}

void perform_signmaster_rotation(int cube[6][9], const char *signmaster_sequence)
{
    int next_is_quote, cur_is_quote;

    /* Loop over chars in the str until we hit the NULL terminator */
	while (*signmaster_sequence != '\0') {
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
		signmaster_sequence++;
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
	case 'X':
            if (reverse) {
                perform_signmaster_rotation(cube, "R'ML");
            } else {
                perform_signmaster_rotation(cube, "RM'L'");
            }
	    break;
	case 'Y':
            if (reverse) {
                perform_signmaster_rotation(cube, "DEU'");
            } else {
                perform_signmaster_rotation(cube, "D'E'U");
            }
	    break;
	case 'Z':
            if (reverse) {
                perform_signmaster_rotation(cube, "F'S'B");
            } else {
                perform_signmaster_rotation(cube, "FSB'");
            }
	    break;
        default:
            fprintf(stderr, "Signmaster rotation %c is not implemented! Aborting..\n", signmaster_letter);
            exit(EXIT_FAILURE);
    }
}

