#include <stdio.h>

#include "mechanics.h"

void rotate_surface(int cube[6][9], int surface, int clockwise)
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

