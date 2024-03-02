#include <iostream>
#include <functional>
#include "dialog/dialog.h"
#include "terminal/terminal.h"

std::vector<std::string> menu1 = {"0. Exit", "1. Add a new warehouse", "2. Delete the warehouse",
                                  "3. Change the size of the warehouse", "4. Go to the warehouse",
                                  "5. Show information", "6. Set the name"};

int main() {
    terminal::Terminal terminal;
    try {
        std::function<int(terminal::Terminal &)> optionFunction[] = {nullptr, dialogAddWarehouse,
                                                                     dialogDeleteWarehouse,
                                                                     dialogChangeWarehouseSize,
                                                                     dialogWarehouse,
                                                                     dialogShow,
                                                                     dialogTerminalSetName};

        int opt;

        while (opt = dialog(menu1)) {
            if (!optionFunction[opt](terminal)) {
                break;
            }
        }

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
