#ifndef ROTATIONS_H
#define ROTATIONS_H

void perform_u_normal(int cube[6][9]);

void perform_u_reverse(int cube[6][9]);

void perform_d_normal(int cube[6][9]);

void perform_d_reverse(int cube[6][9]);

void perform_e_normal(int cube[6][9]);

void perform_e_reverse(int cube[6][9]);

void perform_r_normal(int cube[6][9]);

void perform_r_reverse(int cube[6][9]);

void perform_l_normal(int cube[6][9]);

void perform_l_reverse(int cube[6][9]);

void perform_m_normal(int cube[6][9]);

void perform_m_reverse(int cube[6][9]);

void rotation(int cube[6][9], char signmaster_letter, int reverse);

void perform_signmaster_rotation(int cube[6][9], const char *signmaster_sequence);

#endif
