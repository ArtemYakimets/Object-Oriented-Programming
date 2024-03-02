#ifndef LAB3_TERMINAL_H
#define LAB3_TERMINAL_H

#include <map>
#include  "warehouse.h"

namespace terminal {
    class Terminal {
    private:
        std::string name;
        std::map<int, Warehouse> warehouses;
    public:
        Terminal();
        Terminal(std::string name);
        ~Terminal();

        [[nodiscard]] std::string getName() { return name; }
        [[nodiscard]] Warehouse &getWarehouse(int number);

        void setName(std::string newName) { name = newName; }

        void addWarehouse(int number, Warehouse& warehouse);
        void removeWarehouse(int number);
        void changeWarehouseSize(int number, int newLength, int newWidth, int newHeight);
        std::ostream& print(std::ostream&) const;
    };
}

#endif //LAB3_TERMINAL_H
