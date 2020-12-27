#include "slae_solution.hpp"
#include <limits>

// количество строк в возвращаемом векторе = количество зависимых переменных
// если пусто, то нет решений
std::vector<std::vector<double>> get_SLAE_solution(std::vector<std::vector<double>> A, std::vector<double> B) {

    // ...

    return std::vector<std::vector<double>>();
}


//////////////////////////////////////////////////

int get_number_int(const std::string& name) {

    int number = 0;
    bool good_input = false;

    while (!good_input) {
        std::cout << "Input " << name << ": ";
        std::cin >> number;
        if (std::cin.fail() || (std::cin.peek() != '\n')) {
            std::cin.clear();
            good_input = false;
            std::cout << "Bad_value. It should be integer. Try again!" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            good_input = true;
        }
    }
    return number;
}

double get_number_double(const std::string& name) {

    double number = 0;
    bool good_input = false;

    while (!good_input) {
        std::cout << "Input " << name << ": ";
        std::cin >> number;
        if (std::cin.fail() || (std::cin.peek() != '\n')) {
            std::cin.clear();
            good_input = false;
            std::cout << "Bad_value. It should be real number. Try again!" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            good_input = true;
        }
    }
    return number;
}

void get_A_coefficients(std::vector<std::vector<double>>& A) {

    std::cout << "Input A coefficients" << std::endl;
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            A[i][j] = get_number_double("A_" + std::to_string(i + 1) + "_" + std::to_string(j + 1));
        }
        std::cout << std::endl;
    }
}

void get_B_coefficients(std::vector<double>& B) {

    std::cout << "Input B coefficients" << std::endl;
    for (size_t i = 0; i < B.size(); ++i) {
        B[i] = get_number_double("B_" + std::to_string(i + 1));
    }
    std::cout << std::endl;
}

void print_SLAE(const std::vector<std::vector<double>>& A, const std::vector<double>& B) {

    std::cout << "Your SLAE is" << std::endl;
    for (size_t i = 0; i < B.size(); ++i) {
        for (size_t j = 0; j < A[i].size() - 1; ++j) {
            std::cout << A[i][j] << " * x" << std::to_string(j + 1) << " + ";
        }
        std::cout << A[i][A[i].size() - 1] << " = " << B[i] << std::endl;
    }
    std::cout << std::endl;
}

void print_answer(const std::vector<std::vector<double>>& solution_SLAE) {

    std::cout << "Answer" << std::endl;
    // если пусто, то нет решений
    if(solution_SLAE.empty()) {
        std::cout << "No solution" << std::endl;
        return;
    }

    // количество строк в solution_SlAE = solutionSLAE.size() = количество зависимых переменных
    for (size_t i = 0; i < solution_SLAE.size(); ++i) {
        std::cout << ("x_" + std::to_string(i + 1)) << "= " << solution_SLAE[i][0];
        for (size_t j = 1; j < solution_SLAE[i].size(); ++j) {
            std::cout << " + " << solution_SLAE[i][j] << " * c" << std::to_string(j);
        }
        std::cout << std::endl;
    }
}
