#include <iostream>
#include <vector>
#include "matrix.h"

    Matrix *matrix_insert() {
        Matrix *matrix = new Matrix;

            std::cout << "Enter the number of lines: " << std::endl;
            matrix->m = getNum<int>(0);

            std::cout << "Enter the number of columns" << std::endl;
            matrix->n = getNum<int>(0);

            matrix->head = nullptr;

            for (int i = 1; i < matrix->m + 1; i++) {
                std::cout << "Line " << i << std::endl;
                line_insert(matrix, i);
            }

        return matrix;
    }

    void line_insert(Matrix *matrix, int i) {

            Line *line = new Line;
            line->i = i;
            line->next = nullptr;
            line->head = nullptr;

            for (int j = 1; j < matrix->n + 1; j++)
                item_insert(line, j);

            Line *tmp = matrix->head;
            Line *prev = nullptr;
            while (tmp != nullptr) {
                prev = tmp;
                tmp = tmp->next;
            }
            if (matrix->head != nullptr)
                prev->next = line;
            else
                matrix->head = line;

        }

    void item_insert(Line *line, int ind) {
            std::cout << "Enter the value" << std::endl;
            int value = getNum<int>();

            if (value != 0) {
                Item *tmp = line->head;
                Item *prev = nullptr;
                while (tmp != nullptr) {
                    prev = tmp;
                    tmp = tmp->next;
                }

                Item *item = new Item;
                item->row = line->i;
                item->column = ind;
                item->value = value;
                item->next = nullptr;

                if (line->head != nullptr)
                    prev->next = item;
                else
                    line->head = item;
            }
        }

    void erase(Matrix *matrix) {
        Line *p = matrix->head;
        Line *next = nullptr;
        while (p != nullptr) {
            next = p->next;
            free_line(p);
            p = next;
        }
        delete matrix;
    }

    void free_line(Line *line) {
        Item *p = line->head;
        Item *next = nullptr;
        while (p != nullptr) {
            next = p->next;
            delete p;
            p = next;
        }
        delete line;
    }

    bool isEven (int value) {
        return (value % 2) == 0;
    }

    bool isOdd (int value) {
        return (value % 2) != 0;
    }

    bool is2Digits (int value) {
        return value >= 10;
    }

    void task(Matrix *matrix, std::function<bool(int)> filterFunction) {
        std::vector<int> numbers;

        Line *line = matrix->head;
        while (line != nullptr) {
            int sum = 0;
            Item *item = line->head;
            while (item != nullptr) {
                if (filterFunction(item->value))
                    sum += item->value;
                item = item->next;
            }
            numbers.push_back(sum);
            line = line->next;
        }

        std::cout << "Here is the vector" << std::endl;
        for (int num : numbers)
            std::cout << num << " ";
        std::cout << std::endl;
}

/*
int getNum()
{
    int a;
    std::cin >> a;
    if (!std::cin.good())
        throw std::runtime_error("Failed to read number!");
    return a;
}
 */
