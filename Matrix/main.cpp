#include <iostream>
#include <functional>
#include "matrix.h"
#include "dialog.h"

const char *menu[] = {"0. Quit", "1. Find the sum of even numbers", "2. Find the sum of odd numbers",
                      "3. Find the sum of all elements that contain two and more digits", "4. Print the matrix"};

const int menu_size = sizeof(menu) / sizeof(menu[0]);

int main()
{
    Matrix *matrix = matrix_insert();
    try {
        std::function<int(Matrix *)> optionFunction[] = {nullptr, findEven, findOdd, find2Digits, printMatrix};

        int opt;

        while (opt = dialog(menu, menu_size))
            if (!optionFunction[opt](matrix))
                break;

        std::cout << "Goodbye!" << std::endl;

        erase(matrix);
    }
    catch (const std::bad_alloc& ba) {
        std::cerr << "Not enough memory" << std::endl;
        erase(matrix);
        return 1;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        erase(matrix);
        return 1;
    }
    return 0;
}
