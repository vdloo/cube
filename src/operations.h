#ifndef OPERATIONS_H
#define OPERATIONS_H

int solved_cube[6][9];

void copy_cube(int destination_cube[6][9], int source_cube[6][9]);

void merge_patterns(int destination_cube[6][9], int source_cube[6][9]);

void reset_cube(int cube[6][9]);

void shuffle_cube(int cube[6][9]);

void instantiate_cube(int cube[6][9]);

#endif
