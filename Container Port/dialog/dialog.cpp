#include <functional>
#include <thread>
#include "dialog.h"

std::vector<std::string> menu2 = {"0. Exit", "1. Add a new container", "2. Replace the container",
                                  "3. Delete the container", "4. Add a container automatically",
                                  "5. Get the maximum number of containers", "6. Create a request thread",
                                  "7. Show container's information", "8. Show information"};

int dialog(std::vector<std::string> menu) {

    int choice;
    int size;
    size = menu.size();

    for (int i = 0; i < size; i++)
        std::cout << menu[i] << std::endl;

    choice = getNum<int>(0, size);

    return choice;
}

int dialogAddWarehouse(terminal::Terminal &terminal) {
    std::cout << "Enter the number of the warehouse: " << std::endl;
    int number = getNum<int>(1, 1000);

    std::cout << "Enter the length of the warehouse: " << std::endl;
    int length = getNum<int>(1, 1000);

    std::cout << "Enter the width of the warehouse: " << std::endl;
    int width = getNum<int>(1, 1000);

    std::cout << "Enter the height of the warehouse: " << std::endl;
    int height = getNum<int>(1, 1000);

    std::cout << "Enter the temperature inside the warehouse: " << std::endl;
    int temperature = getNum<int>(-50, 50);

    terminal::Warehouse warehouse(temperature, length, width, height);
    terminal.addWarehouse(number, warehouse);

    return 1;
}

int dialogDeleteWarehouse(terminal::Terminal &terminal) {
    std::cout << "Enter the number of the warehouse: " << std::endl;
    int number = getNum<int>(1, 1000);

    terminal.removeWarehouse(number);

    return 1;
}

int dialogChangeWarehouseSize(terminal::Terminal &terminal) {
    std::cout << "Enter the number of the warehouse: " << std::endl;
    int number = getNum<int>(1, 1000);

    std::cout << "Enter the new length of the warehouse: " << std::endl;
    int length = getNum<int>(1, 1000);

    std::cout << "Enter the new width of the warehouse: " << std::endl;
    int width = getNum<int>(1, 1000);

    std::cout << "Enter the new height of the warehouse: " << std::endl;
    int height = getNum<int>(1, 1000);

    terminal.changeWarehouseSize(number, length, width, height);

    return 1;
}

int dialogWarehouse(terminal::Terminal &terminal) {
    std::cout << "Enter the number of the warehouse: " << std::endl;
    int number = getNum<int>(1, 1000);

    terminal::Warehouse warehouse = terminal.getWarehouse(number);
    try {
        std::function<int(terminal::Warehouse &)> optionFunction[] = {nullptr, dialogAddContainer,
                                                                      dialogReplaceContainer,
                                                                      dialogDeleteContainer,
                                                                      dialogAddContainerAuto,
                                                                      dialogGetMaximumContainers,
                                                                      dialogCreateRequestThread,
                                                                      dialogContainerShow,
                                                                      dialogWarehouseShow};

        int opt;

        while (opt = dialog(menu2))
            if (!optionFunction[opt](warehouse))
                break;

    }
    catch (const std::bad_alloc& ba) {
        std::cerr << "Not enough memory" << std::endl;
        return 1;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 1;
}

int dialogShow(terminal::Terminal &terminal) {
    std::cout << "Here is the terminal: " << std::endl;
    terminal.print(std::cout);

    return 1;
}

int dialogTerminalSetName(terminal::Terminal &terminal) {
    std::cout << "Enter a new terminal's name: " << std::endl;
    std::string name;
    std::cin >> name;
    terminal.setName(name);

    return 1;
}

int dialogAddContainer(terminal::Warehouse &warehouse) {
    std::cout << "Enter the container type: " << std::endl;
    std::cout << "1. Regular" << std::endl;
    std::cout << "2. Chilled" << std::endl;
    std::cout << "3. Fragile" << std::endl;
    std::cout << "4. FragileChilled" << std::endl;
    int choice = getNum<int>(1, 4);

    std::cout << "Enter the number: " << std::endl;
    int number = getNum<int>(1, 1000);

    std::cout << "Enter the name: " << std::endl;
    std::string name;
    std::cin >> name;

    std::cout << "Enter the length: " << std::endl;
    int length = getNum<int>(1, 1000);

    std::cout << "Enter the width: " << std::endl;
    int width = getNum<int>(1, 1000);

    std::cout << "Enter the height: " << std::endl;
    int height = getNum<int>(1, 1000);

    std::cout << "Enter the weight: " << std::endl;
    int weight = getNum<int>(1, 100000);

    std::cout << "Enter the cost: " << std::endl;
    int cost = getNum<int>(0);

    int temperature;
    if (choice == 2 || choice == 4) {
        std::cout << "Enter the maximum temperature: " << std::endl;
        temperature = getNum<int>(-50, 50);
    }

    int max_weight;
    if (choice == 3 || choice == 4) {
        std::cout << "Enter the maximum weight above: " << std::endl;
        max_weight = getNum<int>(1, 100000);
    }

    std::cout << "Enter the minimum point " << std::endl;
    std::cout << "x :" << std::endl;
    int min_x = getNum<int>(0, 1000);
    std::cout << "y :" << std::endl;
    int min_y = getNum<int>(0, 1000);
    std::cout << "z :" << std::endl;
    int min_z = getNum<int>(0, 1000);

    std::cout << "Enter the maximum point " << std::endl;
    std::cout << "x :" << std::endl;
    int max_x = getNum<int>(0, 1000);
    std::cout << "y :" << std::endl;
    int max_y = getNum<int>(0, 1000);
    std::cout << "z :" << std::endl;
    int max_z = getNum<int>(0, 1000);

    if (choice == 1) {
        terminal::Container c(number, name, length, width, height, weight, cost);
        terminal::ContainerSpace cs(min_x, min_y, min_z, max_x, max_y, max_z, c);
        warehouse.insertContainerWithCoordinates(cs);
    }
    if (choice == 2) {
        terminal::ChilledContainer c(number, name, length, width, height, weight, cost, temperature);
        terminal::ContainerSpace cs(min_x, min_y, min_z, max_x, max_y, max_z, c);
        warehouse.insertContainerWithCoordinates(cs);
    }
    if (choice == 3) {
        terminal::FragileContainer c(number, name, length, width, height, weight, cost, max_weight);
        terminal::ContainerSpace cs(min_x, min_y, min_z, max_x, max_y, max_z, c);
        warehouse.insertContainerWithCoordinates(cs);
    }
    if (choice == 4) {
        terminal::FragileChilledContainer c(number, name, length, width, height, weight, cost, temperature, max_weight);
        terminal::ContainerSpace cs(min_x, min_y, min_z, max_x, max_y, max_z, c);
        warehouse.insertContainerWithCoordinates(cs);
    }

    return 1;
}

int dialogReplaceContainer(terminal::Warehouse &warehouse) {
    std::cout << "Enter the number: " << std::endl;
    int number = getNum<int>(1, 1000);

    std::cout << "Enter the minimum point " << std::endl;
    std::cout << "x :" << std::endl;
    int min_x = getNum<int>(0, 1000);
    std::cout << "y :" << std::endl;
    int min_y = getNum<int>(0, 1000);
    std::cout << "z :" << std::endl;
    int min_z = getNum<int>(0, 1000);

    std::cout << "Enter the maximum point " << std::endl;
    std::cout << "x :" << std::endl;
    int max_x = getNum<int>(0, 1000);
    std::cout << "y :" << std::endl;
    int max_y = getNum<int>(0, 1000);
    std::cout << "z :" << std::endl;
    int max_z = getNum<int>(0, 1000);

    terminal::Container c;
    terminal::ContainerSpace cs(min_x, min_y, min_z, max_x, max_y, max_z, c);

    warehouse.replaceContainer(number, cs);
    return 1;
}

int dialogDeleteContainer(terminal::Warehouse &warehouse) {
    std::cout << "Enter the number: " << std::endl;
    int number = getNum<int>(1, 1000);

    warehouse.removeContainer(number);
    return 1;
}

int dialogAddContainerAuto(terminal::Warehouse &warehouse) {
    std::cout << "Enter the container type: " << std::endl;
    std::cout << "1. Regular" << std::endl;
    std::cout << "2. Chilled" << std::endl;
    std::cout << "3. Fragile" << std::endl;
    std::cout << "4. FragileChilled" << std::endl;
    int choice = getNum<int>(1, 4);

    std::cout << "Enter the number: " << std::endl;
    int number = getNum<int>(1, 1000);

    std::cout << "Enter the name: " << std::endl;
    std::string name;
    std::cin >> name;

    std::cout << "Enter the length: " << std::endl;
    int length = getNum<int>(1, 1000);

    std::cout << "Enter the width: " << std::endl;
    int width = getNum<int>(1, 1000);

    std::cout << "Enter the height: " << std::endl;
    int height = getNum<int>(1, 1000);

    std::cout << "Enter the weight: " << std::endl;
    int weight = getNum<int>(1, 100000);

    std::cout << "Enter the cost: " << std::endl;
    int cost = getNum<int>(0);

    int temperature;
    if (choice == 2 || choice == 4) {
        std::cout << "Enter the maximum temperature: " << std::endl;
        temperature = getNum<int>(-50, 50);
    }

    int max_weight;
    if (choice == 3 || choice == 4) {
        std::cout << "Enter the maximum weight above: " << std::endl;
        max_weight = getNum<int>(1, 100000);
    }

    if (choice == 1) {
        terminal::Container c(number, name, length, width, height, weight, cost);
        warehouse.insertContainer(c);
    }
    if (choice == 2) {
        terminal::ChilledContainer c(number, name, length, width, height, weight, cost, temperature);
        warehouse.insertContainer(c);
    }
    if (choice == 3) {
        terminal::FragileContainer c(number, name, length, width, height, weight, cost, max_weight);
        warehouse.insertContainer(c);
    }
    if (choice == 4) {
        terminal::FragileChilledContainer c(number, name, length, width, height, weight, cost, temperature, max_weight);
        warehouse.insertContainer(c);
    }

    return 1;
}

int dialogGetMaximumContainers(terminal::Warehouse &warehouse) {
    std::cout << "Enter the length: " << std::endl;
    int length = getNum<int>(1, 1000);

    std::cout << "Enter the width: " << std::endl;
    int width = getNum<int>(1, 1000);

    std::cout << "Enter the height: " << std::endl;
    int height = getNum<int>(1, 1000);

    terminal::Container c(1, "1", length, width, height, 1, 1);
    warehouse.getMaxNumberOfContainers(c);
    return 1;
}

int dialogCreateRequestThread(terminal::Warehouse &warehouse) {
    std::cout << "Enter the number of requests: " << std::endl;
    int num = getNum<int>(1, 20);

    for (int i = 0; i < num; i++)
        dialogAddContainerAuto(warehouse);

    return 1;
}

int dialogWarehouseShow(terminal::Warehouse &warehouse) {
    std::cout << "Here is the warehouse: " << std::endl;
    warehouse.print(std::cout);
    return 1;
}

int dialogContainerShow(terminal::Warehouse &warehouse) {
    std::cout << "Enter the number: " << std::endl;
    int num = getNum<int>(1, 1000);

    warehouse.showContainer(num);
    return 1;
}





