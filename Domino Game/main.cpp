#include <iostream>
#include <functional>
#include <ctime>
#include "domino/dialog.h"

const char *menu[] = {"0. Quit", "1. Add a random domino bone", "2. Remove a random domino bone",
                      "3. Remove the domino bone by its values", "4. Remove the domino bone by its index",
                      "5. Find the domino bone by its index", "6. Sort the domino group in ascending order",
                      "7. Extract a subgroup by value", "8. Print the domino group", "9. Do a task for simple class"};

const int menu_size = sizeof(menu) / sizeof(menu[0]);

int progForDomino(lab2::DominoGroup &group);

int main()
{
    srand(time(nullptr));
    try {
        lab2::DominoGroup group = lab2::DominoGroup::createGroupWithAllTypes(1);

        std::function<int(lab2::DominoGroup &)> optionFunction[] = {nullptr, dialogAddRandomBone, dialogRemoveRandomBone,
                                                                  dialogRemoveDominoByValues, dialogRemoveDominoByIndex,
                                                                  dialogFindDominoByIndex, dialogSort,
                                                                  dialogExtractSubgroupByValue, dialogPrintDominoGroup,
                                                                  progForDomino};

        int opt;

        while (opt = dialog(menu, menu_size))
            if (!optionFunction[opt](group))
                break;

        std::cout << "Goodbye!" << std::endl;
    }
    catch (const std::bad_alloc& ba) {
        std::cerr << "Not enough memory" << std::endl;
        return 1;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

int progForDomino(lab2::DominoGroup &group) {
    lab2::Domino bone1(3, 5);
    lab2::Domino bone2 = lab2::Domino::createRandomDomino();

    bone1.displayAsciiArt();
    std::cout << std::endl;
    bone2.displayAsciiArt();

    if (bone1 == bone2) {
        std::cout << "Dominoes are equal" << std::endl;
    } else {
        std::cout << "Dominoes are not equal" << std::endl;
    }

    bone1 = ~bone1;
    std::cout << bone1 << std::endl;

    return 1;
}
