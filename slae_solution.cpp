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
    if(solution_SLAE.empty()) {
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
            } else {
                // нашли свободную
                free_vars[column] = ci;
                ++ci;
                ++column;
                // проверяем, есть ли в строке базисная
                while (column < (solution_SLAE[line].size() - 1)) {

                    if (solution_SLAE[line][column] != 0) {
                        // наткнулись на базисную
                        ++base_vars_cnt;
                        ++line;
                        ++column;
                        break;
                    } else {
                        // наткнулись на свободную
                        free_vars[column] = ci;
                        ++ci;
                        ++column;
                    }
                }
            }
        } else {
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
        std::cout << ("x_" + std::to_string(pos_of_base_var + 1)) << " = " << solution_SLAE[i][solution_SLAE[i].size() - 1];


        // выводим комбинацию из свободных переменных
        for (size_t j = pos_of_base_var + 1; j < solution_SLAE[i].size() - 1; ++j) {
            if (solution_SLAE[i][j] != 0) {
                std::cout << " + " << -solution_SLAE[i][j] << " * c" << std::to_string(free_vars[j]);
            }
        }
        std::cout << std::endl;

        // корректируем позицию поиска следующей базисной переменной
        ++pos_of_base_var;
    }

    // вывод свободных переменных
    for (size_t i = 0; i < free_vars.size(); ++i) {
        if(free_vars[i] != 0) {
            std::cout << "x_" + std::to_string(i + 1) << " = " << "c" << std::to_string(free_vars[i]);
            std::cout << std::endl;
        }
    }
}
