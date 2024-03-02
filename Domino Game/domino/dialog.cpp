#include "dialog.h"
#include <iostream>

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

int dialogAddRandomBone(lab2::DominoGroup &group) {
    lab2::Domino domino = lab2::Domino::createRandomDomino();
    group.addDomino(domino);
    return 1;
}

int dialogRemoveRandomBone(lab2::DominoGroup &group) {
    if (group.getSize() <= 0)
        throw std::out_of_range("The group is empty!");

    int index = rand() % group.getSize();
    lab2::Domino bone = group.removeDominoByIndex(index);
    bone.displayAsciiArt();
    return 1;
}

int dialogRemoveDominoByValues(lab2::DominoGroup &group) {
    std::cout << "Enter the first value: " << std::endl;
    int value1 = getNum(1, 6);

    std::cout << "Enter the second value: " << std::endl;
    int value2 = getNum(1, 6);

    lab2::Domino bone(value1, value2);
    bone = group.removeDomino(bone);
    bone.displayAsciiArt();
    return 1;
}

int dialogRemoveDominoByIndex(lab2::DominoGroup &group) {
    try {
        std::cout << "Enter the index: " << std::endl;
        int index = getNum(0);

        lab2::Domino bone = group.removeDominoByIndex(index);
        bone.displayAsciiArt();
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int dialogFindDominoByIndex(lab2::DominoGroup &group) {
    try {
        std::cout << "Enter the index: " << std::endl;
        int index = getNum(0);

        lab2::Domino bone = group[index];
        bone.displayAsciiArt();
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int dialogSort(lab2::DominoGroup &group) {
    group.sortBySumAscending();
    group.print();
    return 1;
}

int dialogExtractSubgroupByValue (lab2::DominoGroup &group) {
    std::cout << "Enter the value: " << std::endl;
    int value = getNum(1, 6);

    group.extractSubgroup(value);
    group.print();
    return 1;
}

int dialogPrintDominoGroup (lab2::DominoGroup &group) {
    std::cout << "Here is the domino group: " << std::endl;
    group.print();
    return 1;
}