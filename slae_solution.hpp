#ifndef SLAE_SOLUTION_HPP
#define SLAE_SOLUTION_HPP

// system of linear algebraic equations

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

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

// Find a nonzero element in the j-th row
size_t find_nonzero_element(std::vector<std::vector<double>>& A, size_t j);

// Swapping lines
void change_string(std::vector<std::vector<double>>& A, std::vector<double>& B, size_t i, size_t j);

// Divide a string by a number
void division(std::vector<std::vector<double>>& A, std::vector<double>& B, size_t j, size_t index);

// Subtract one line from another
void subtraction_strings(std::vector<std::vector<double>>& A, std::vector<double>& B, size_t j, size_t index);

// Matrix compatibility check
bool check_compatibility(std::vector<std::vector<double>>& A, std::vector<double>& B);

// Bringing it to the form: one line one basic variable
void find_base_variables(std::vector<std::vector<double>>& A, std::vector<double>& B);

#endif // SLAE_SOLUTION_HPP