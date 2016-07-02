#ifndef STATUS_H
#define STATUS_H

int count_mismatches(int cube[6][9], int desired_state[6][9]);
int check_solved(int cube[6][9]);
void print_cube_solved_status(int cube[6][9]);

#endif
