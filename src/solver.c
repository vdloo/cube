#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solver.h"
#include "patterns.h"
#include "mechanics.h"
#include "rotations.h"
#include "representation.h"
#include "status.h"
#include "operations.h"

#define BUFFER_LENGTH 512

int path_to_solved[BUFFER_LENGTH];
int buffer_counter = 0;

int look_at_depth(int cube[6][9], int desired_state[6][9], int depth, int distance, int history[])
{
    int move, state;
    if (depth == 0) {
        state = count_mismatches(cube, desired_state);
	if (state <= distance) {
	    printf("Found a solution!\n");
	}
	return state;
    } else {
	int test_cube[6][9];
	int found_distance;
	for (move = 0; move < ALL_ROTATIONS; move++) {
	    copy_cube(test_cube, cube);
	    history[depth - 1] = move;
	    perform_singmaster_rotation(test_cube, singmaster_rotations[move]);
	    found_distance = look_at_depth(test_cube, desired_state, depth - 1, distance, history);
	    if (found_distance <= distance) {
               return found_distance; 
	    }
	}
    }
    return 1;
}

int iterative_deepening(int cube[6][9], int destination_cube[6][9], int distance, int max_depth)
{
     int depth = 0;

     int history[max_depth], i;
     for (i = 0; i < max_depth; i++) {
         history[i] = -1;
     }

     while (look_at_depth(cube, destination_cube, depth, distance, history) > distance) {
         if (depth >= max_depth) {
	     printf("Not allowed to look further than %d moves.\n", max_depth);
	     fprintf(stderr, "Failed to find a solution!\n");
	     exit(EXIT_FAILURE);
         }
         depth++;
	 printf("checking %d levels deep\n", depth);
     }

     printf("Path is: ");
     int move;
     for (i = max_depth; i > 0; i--) {
         move = history[i - 1]; 
	 if (move != -1) {
             perform_singmaster_rotation(cube, singmaster_rotations[move]);
             printf("%s", singmaster_rotations[move]);
             if (buffer_counter > BUFFER_LENGTH) {
	         fprintf(stderr, "Exceeded the maximum amount of moves that fit in the buffer!: %d", BUFFER_LENGTH);
	         exit(EXIT_FAILURE);
             }
             path_to_solved[buffer_counter] = move;
	     buffer_counter++;
	 }
     }
     printf("\n");
     printf("Distance to destination pattern is %d\n", distance);
     return 0;
}

void yellow_cross_solver(int cube[6][9])
{
     int i;
     for (i = 0; i < BUFFER_LENGTH; i++) {
         path_to_solved[i] = -1;
     }

     int pattern[6][9];
     int before_solve_state[6][9];
     copy_cube(before_solve_state, cube);

     printf("Finding a solution\n");

     printf("Putting the white face on the top surface\n");
     copy_cube(pattern, white_face_on_top_pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nCreating the white cross pattern by aligning one edge\n");
     merge_patterns(pattern, front_white_edge_on_top_pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(pattern);
     print_cube(cube);

     printf("\nCreating the white cross pattern by aligning two edges\n");
     merge_patterns(pattern, right_white_edge_on_top_pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(pattern);
     print_cube(cube);

     printf("\nCreating the white cross pattern by aligning three edges\n");
     merge_patterns(pattern, back_white_edge_on_top_pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(pattern);
     print_cube(cube);

     printf("\nCreating the white cross pattern by aligning four edges\n");
     merge_patterns(pattern, left_white_edge_on_top_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving the first layer by aligning one corner\n");
     merge_patterns(pattern, one_white_corners_on_top_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving the first layer by aligning two corners\n");
     merge_patterns(pattern, two_white_corners_on_top_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving the first layer by aligning three corners\n");
     merge_patterns(pattern, three_white_corners_on_top_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving the first layer by aligning four corners\n");
     merge_patterns(pattern, all_white_corners_on_top_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 2 corner 1\n");
     merge_patterns(pattern, second_layer_first_corner_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 2 corner 2\n");
     merge_patterns(pattern, second_layer_second_corner_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);
     
     printf("\nSolving layer 2 corner 3\n");
     merge_patterns(pattern, second_layer_third_corner_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 2 corner 4\n");
     merge_patterns(pattern, second_layer_fourth_corner_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 3 yellow cross \n");
     copy_cube(pattern, white_face_on_top_pattern);
     merge_patterns(pattern, third_layer_yellow_cross_pattern);
     print_cube(third_layer_yellow_cross_pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 3 yellow edges \n");
     merge_patterns(pattern, third_layer_yellow_edges_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 3 first corner \n");
     merge_patterns(pattern, third_layer_first_corner_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 3 second corner \n");
     merge_patterns(pattern, third_layer_second_corner_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 3 third corner \n");
     merge_patterns(pattern, third_layer_third_corner_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 3 fourth corner \n");
     merge_patterns(pattern, third_layer_fourth_corner_pattern);
     print_cube(pattern);
     iterative_deepening(cube, pattern, 0, 8);
     print_cube(cube);

     printf("\nSolving layer 3\n");
     iterative_deepening(cube, solved_cube, 0, 8);
     print_cube(cube);

     print_cube_solved_status(cube);

     printf("\n\nCube pre-solved state: \n");
     print_cube(before_solve_state);

     printf("Solved cube with %d moves: ", buffer_counter);
     int move;
     for (i = 0; i < BUFFER_LENGTH; i++) {
         move = path_to_solved[i];
         if (move == -1) {
             break;
         }
         printf("%s", singmaster_rotations[move]);
         path_to_solved[i] = -1;
     }
     printf("\n");
}

