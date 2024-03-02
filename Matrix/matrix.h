#ifndef LAB1_MATRIX_H
#define LAB1_MATRIX_H

#include <iostream>
#include <limits>
#include <string>
#include <cstring>
#include <functional>


    struct Item
    {
        int row;
        int column;
        int value;
        Item *next;
    };

    struct Line
    {
        int i;
        Item *head;
        Line *next;
    };

    struct Matrix {
        int m;
        int n;
        Line *head;
    };

    template <class T>
    T getNum (T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while (true) {
            std::cin >> a;
            if (std::cin.eof())
                throw std::runtime_error("Failed to read number: EOF");
            else if (std::cin.bad()) {
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            }
            else if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Try again!" << std::endl;
            }
            else if (a >= min && a <= max)
                return a;
        }
    }

    Matrix *matrix_insert();
    void line_insert(Matrix *, int);
    void item_insert(Line *, int );
    void erase(Matrix *);
    void free_line(Line *);
    bool isEven(int);
    bool isOdd(int);
    bool is2Digits(int);
    void task(Matrix *, std::function<bool(int)>);


#endif //LAB1_MATRIX_H
