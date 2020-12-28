#include <iostream>
#include <vector>
#include "slae_solution.hpp"

// uncomment to test
#define TEST

int main() {
#ifndef TEST
    std::cout << "SLAE_solution" << std::endl;

    // get equation_count > 0
    int n = 0;
    while (n <= 0) {
        std::cout << "equation_count > 0" << std::endl;
        n = get_number_int("equation_count");
    }

    // get vars_count > 0
    int m = 0;
    while (m <= 0) {
        std::cout << "vars_count > 0" << std::endl;
        m = get_number_int("vars_count");
    }

    // get coefficients of system
    std::vector<std::vector<double>> A(n, std::vector<double>(m, 0));
    std::vector<double> B(n, 0);
    get_A_coefficients(A);
    get_B_coefficients(B);

    // show system
    print_SLAE(A, B);

    // solution
    std::vector<std::vector<double>> solution_SLAE;
    // количество строк в solution_SlAE = solutionSLAE.size() = количество зависимых переменных
    // если пусто, то нет решений
    solution_SLAE = get_SLAE_solution(A, B);
    print_answer(solution_SLAE);
#else // TEST

    //int n = 4;
    //int m = 4;
    std::vector<std::vector<double>> A{{1, -1, 1, -1}, {1, 1, 2, 3}, {2, 4, 5, 10}, {2, -4, 1, -6}};
    std::vector<double> B{4, 8, 20, 4};
    print_SLAE(A, B);

    // solution
    // std::vector solution_SLAE = get_SLAE_solution(A, B);

    // ожидается:
    std::vector<std::vector<double>> solution_SLAE{{1, 0, 1.5, 1, 6} , {0, 1, 0.5, 2, 2}};

    // должен быть вывод:
    // x_1 = 6 + -1.5 * c_1 + -1 * c_2
    // x_2 = 2 + -0.5 * c_1 + -2 * c_2
    // x_3 = c1
    // x_4 = c2
    print_answer(solution_SLAE);


#endif


    return 0;
}
