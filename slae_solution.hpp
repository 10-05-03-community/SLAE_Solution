#ifndef SLAE_SOLUTION_HPP
#define SLAE_SOLUTION_HPP

// system of linear algebraic equations

#include <iostream>
#include <string>
#include <vector>

// solve SLAE
std::vector<std::vector<double>> get_SLAE_solution(std::vector<std::vector<double>> A, std::vector<double> B);

// get coefficients of vars
void get_A_coefficients(std::vector<std::vector<double>>& A);

// get coefficients of free members
void get_B_coefficients(std::vector<double>& B);

// input interger var with name "name"
int get_number_int(const std::string& name);

// input real var with name "name"
double get_number_double(const std::string& name);

// correct output of answer
void print_answer(const std::vector<std::vector<double>>& solution_SLAE);

// show all system
void print_SLAE(const std::vector<std::vector<double>>& A, const std::vector<double>& B);

#endif // SLAE_SOLUTION_HPP
