#ifndef LAB3_DIALOG_H
#define LAB3_DIALOG_H

#include <iostream>
#include <limits>
#include <cstring>
#include "../terminal/terminal.h"

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

int dialog(std::vector<std::string> menu);
int dialogAddWarehouse(terminal::Terminal &terminal);
int dialogDeleteWarehouse(terminal::Terminal &terminal);
int dialogChangeWarehouseSize(terminal::Terminal &terminal);
int dialogWarehouse(terminal::Terminal &terminal);
int dialogShow(terminal::Terminal &terminal);
int dialogTerminalSetName(terminal::Terminal &terminal);

int dialogAddContainer(terminal::Warehouse &warehouse);
int dialogReplaceContainer(terminal::Warehouse &warehouse);
int dialogDeleteContainer(terminal::Warehouse &warehouse);
int dialogAddContainerAuto(terminal::Warehouse &warehouse);
int dialogGetMaximumContainers(terminal::Warehouse &warehouse);
int dialogCreateRequestThread(terminal::Warehouse &warehouse);
int dialogWarehouseShow(terminal::Warehouse &warehouse);
int dialogContainerShow(terminal::Warehouse &warehouse);


#endif //LAB3_DIALOG_H
