#include "slae_solution.hpp"
#include <limits>

// количество строк в возвращаемом векторе = количество зависимых переменных
// если пусто, то нет решений
std::vector<std::vector<double>> get_SLAE_solution(std::vector<std::vector<double>> A, std::vector<double> B) {

    for (size_t j = 0; j < A[0].size(); ++j) {

        size_t i = find_nonzero_element(A, j);

        if (i != -1) {
            change_string(A, B, i, j);
            division(A, B, j, j);
            subtraction_strings(A, B, j, j);
        }

    }

    if (check_compatibility(A, B)) {

        find_base_variables(A, B);

        std::vector<std::vector<double>> A_B(A.size(), std::vector<double>(A[0].size() + 1, 0));

        for (size_t i = 0; i < A_B.size(); ++i) {
            for (size_t j = 0; j < A_B[0].size(); ++j) {
                if (j == A_B[0].size() - 1) {
                    A_B[i][j] = B[i];
                }
                else {
                    A_B[i][j] = A[i][j];
                }
            }
        }
        return A_B;
    }

    return std::vector<std::vector<double>>();
}

size_t find_nonzero_element(std::vector<std::vector<double>>& A, size_t j) {

    for (size_t i = j; i < A.size(); ++i) {
        if (A[i][j] != 0) {
            return i;
        }
    }

    return -1;
}

void change_string(std::vector<std::vector<double>>& A, std::vector<double>& B, size_t i, size_t j) {

    for (size_t k = 0; k < A[i].size(); ++k) {
        double a = A[j][k];
        A[j][k] = A[i][k];
        A[i][k] = a;
    }

    double b = B[j];
    B[j] = B[i];
    B[i] = b;
}

void division(std::vector<std::vector<double>>& A, std::vector<double>& B, size_t j, size_t index) {
    double a = A[j][index];

    for (size_t k = 0; k < A[j].size(); ++k) {
        A[j][k] /= a;
    }

    B[j] /= a;
}

void subtraction_strings(std::vector<std::vector<double>>& A, std::vector<double>& B, size_t j, size_t index) {

    for (size_t i = 0; i < A.size(); ++i) {

        double coefficient = A[i][index];

        if (i == j) {
            continue;
        }

        for (size_t k = 0; k < A[j].size(); ++k) {
            A[i][k] -= coefficient * A[j][k];
            if (fabs(A[i][k]) < 0.00000001) {
                A[i][k] = 0;
            }
        }

        B[i] -= coefficient * B[j];
        if (fabs(B[i]) < 0.00000001) {
            B[i] = 0;
        }
    }

}

bool check_compatibility(std::vector<std::vector<double>>& A, std::vector<double>& B) {

    for (size_t i = 0; i < A.size(); ++i) {

        size_t count = 0;

        for (size_t j = 0; j < A[0].size(); ++j) {

            if (A[i][j] == 0) {
                count++;
            }
            else {
                break;
            }
        }

        if (count == A[0].size()) {

            if (B[i] != 0) {
                return false;
            }

            A.erase(A.begin() + i);
            B.erase(B.begin() + i);
            --i;
        }
    }

    return true;
}

void find_base_variables(std::vector<std::vector<double>>& A, std::vector<double>& B) {

    std::unordered_set <size_t> base_variables;

    for (size_t i = 0; i < A.size(); ++i) {

        if (A[i][i] != 0 and base_variables.find(i) == base_variables.end()) {
            base_variables.insert(i);
        }
        else {
            for (size_t j = i; j < A[i].size(); ++j) {

                if (A[i][j] != 0 and base_variables.find(j) == base_variables.end()) {
                    base_variables.insert(j);
                }
            }
        }
    }

    auto iter = base_variables.begin();

    for (size_t i = 0; i < A.size(); ++i) {
        division(A, B, i, *iter);
        subtraction_strings(A, B, i, *iter);
        iter++;
    }
}

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
        }
        else {
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
        }
        else {
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
        std::cout << A[i][A[i].size() - 1] << " * x" + std::to_string(A[i].size()) << " = " << B[i] << std::endl;
    }
    std::cout << std::endl;
}

void print_answer(const std::vector<std::vector<double>>& solution_SLAE) {

    // предполагается, что матрица имеет ступенчатый вид
    // и содержит base_vars_cnt строк по base_vars_cnt + free_vars_cnt + 1 столбцов
    // последний столбец - свободные члены

    std::cout << "Answer" << std::endl;

    // если пусто, то нет решений
    if (solution_SLAE.empty()) {
        std::cout << "No solution" << std::endl;
        return;
    }

    // число базисных переменных
    // считаем, что изначально все свободные
    size_t base_vars_cnt = 0;

    // число свободных переменных
    size_t free_vars_cnt = solution_SLAE[0].size() - 1;

    // свободные переменные имеют значения ci, i = 1, 2 и т.д.
    // в этом векторе храним индекс с, для базисных индекс i у с = 0
    std::vector<size_t> free_vars(free_vars_cnt + base_vars_cnt, 0);

    // присваиваем значения индексов i у с свободным переменным для корректного вывода базисных
    size_t ci = 1;
    size_t column = 0;
    size_t line = 0;
    while ((column < solution_SLAE[0].size() - 1)) {
        // если ещё в матрице
        if ((line < solution_SLAE.size())) {
            // подразумеваем, что коэф. перед базисными уже = 1
            if (solution_SLAE[line][column] != 0) {
                // нашли базисную
                ++base_vars_cnt;
                ++line;
                ++column;
            }
            else {
                // нашли свободную
                free_vars[column] = ci;
                ++ci;
                ++column;
            }
        }
        else {
            // вышли из матрицы, но прошлись не по всем переменным
            // остались свободные
            // здесь line <= column < free_vars.size
            free_vars[column] = ci;
            ++ci;
            ++column;
        }
    }

    // вывод базисных переменных
    size_t pos_of_base_var = 0;
    for (size_t i = 0; i < base_vars_cnt; ++i) {

        // если номер строки не равен номеру базисных переменной, то найдём текущую базисную
        while (free_vars[pos_of_base_var] != 0) {
            ++pos_of_base_var;
        }

        // выводим свободный член
        std::cout << "x_" << (pos_of_base_var + 1) << " = " << solution_SLAE[i][solution_SLAE[i].size() - 1];

        // выводим комбинацию из свободных переменных
        for (size_t j = pos_of_base_var + 1; j < solution_SLAE[i].size() - 1; ++j) {
            if (solution_SLAE[i][j] != 0) {
                std::cout << " + " << -solution_SLAE[i][j] << " * c" << free_vars[j];
            }
        }
        std::cout << std::endl;

        // корректируем позицию поиска следующей базисной переменной
        ++pos_of_base_var;
    }

    // вывод свободных переменных
    for (size_t i = 0; i < free_vars.size(); ++i) {
        if (free_vars[i] != 0) {
            std::cout << "x_" << (i + 1) << " = c" << free_vars[i] << std::endl;
        }
    }
}