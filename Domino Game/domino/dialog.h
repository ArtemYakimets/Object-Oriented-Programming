#ifndef LAB2A_DIALOG_H
#define LAB2A_DIALOG_H


#include <limits>
#include <iostream>
#include <cstring>
#include "domino_group.h"

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
        else
            std::cout << "Try again!" << std::endl;
    }
}

int dialog(const char **, int);
int dialogAddRandomBone(lab2::DominoGroup &group);
int dialogRemoveRandomBone(lab2::DominoGroup &group);
int dialogRemoveDominoByValues(lab2::DominoGroup &group);
int dialogRemoveDominoByIndex(lab2::DominoGroup &group);
int dialogFindDominoByIndex(lab2::DominoGroup &group);
int dialogSort(lab2::DominoGroup &group);
int dialogExtractSubgroupByValue (lab2::DominoGroup &group);
int dialogPrintDominoGroup (lab2::DominoGroup &group);

#endif //LAB2A_DIALOG_H
