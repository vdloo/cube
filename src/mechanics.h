#ifndef MECHANICS_H
#define MECHANICS_H

void rotate_surface(int cube[6][9], int surface, int clockwise);

void rotate_left_right(int cube[6][9], int layer, int clockwise);

void rotate_up_down(int cube[6][9], int layer, int clockwise);

#endif
