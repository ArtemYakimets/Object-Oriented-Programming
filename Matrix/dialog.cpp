#include <iostream>
#include <string>
#include "dialog.h"

int dialog(const char *menu[], int menu_size)
{
    int choice;
    try
    {
        std::string errmsg = "";
        int status;

        do {
            std::cout << errmsg << std::endl;
            errmsg = "Error: incorrect number entered! Try again";

            for (int i = 0; i < menu_size; i++)
                std::cout << menu[i] << std::endl;

            std::cout << "Enter the number of choice: " << std::endl;

            choice = getNum<int>();
        } while (choice < 0 || choice >= menu_size);
    }
    catch (...) {
        throw;
    }
    return choice;
};

int findEven(Matrix *matrix)
{
    int s = 0;
    task(matrix, [&s](int value){ if (value % 2 == 0) { s += value; return true;} else { return false;}; });
    std::cout << s << std::endl;
    return 1;
}

int findOdd(Matrix *matrix)
{
    task(matrix, isOdd);
    return 1;
}

int find2Digits(Matrix *matrix)
{
    task(matrix, is2Digits);
    return 1;
}

int printMatrix(Matrix *matrix)
{
    std::cout << "Here is the matrix: " << std::endl;
    Line *line = matrix->head;
    while (line != nullptr) {
        Item *item = line->head;
        if (item == nullptr) {
            for (int i = 0; i < matrix->n; i++)
                std::cout << "0 ";
        }

        int i = 1;
        while (item != nullptr) {
            if (item->column == i) {
                std::cout << item->value << " ";
                item = item->next;
            }
            else
                std::cout << "0 ";
            i++;
        }
        if (i < matrix->n + 1) {
            for (int k = i; k < matrix->n + 1; k++)
                std::cout << "0 ";
        }
        std::cout << std::endl;
        line = line->next;
    }
    return 1;
}