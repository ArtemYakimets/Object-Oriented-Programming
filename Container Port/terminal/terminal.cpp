#include <iostream>
#include "terminal.h"

terminal::Terminal::Terminal() {
    name = "untitled";
}

terminal::Terminal::Terminal(std::string name) {
    this->name = std::move(name);
}

std::ostream &terminal::Terminal::print(std::ostream &os) const{
    os << "### " << name << " ###" << std::endl;
    os << "Number of warehouses: " << warehouses.size() << std::endl;
    for (const auto &pair : warehouses)
        os << "№" << pair.first << std::endl;
    return os;
}

void terminal::Terminal::addWarehouse(int number, terminal::Warehouse &warehouse) {
    auto result = warehouses.emplace(number, warehouse);
    if (!result.second)
        throw std::runtime_error("Cannot insert the element: such a key is already exists");
}

void terminal::Terminal::removeWarehouse(int number) {
    auto it = warehouses.find(number);
    if (it != warehouses.end()) {
        warehouses.erase(it);
    } else {
        throw std::runtime_error("Warehouse with given number does not exist");
    }
}

void terminal::Terminal::changeWarehouseSize(int number, int newLength, int newWidth, int newHeight) {
    auto it = warehouses.find(number);
    if (it != warehouses.end()) {
        if (it->second.getLength() < newLength || it->second.getWidth() < newWidth || it->second.getHeight() < newHeight)
            throw std::runtime_error("The new size must be greater than old size");
        else {
            it->second.setLength(newLength);
            it->second.setWidth(newWidth);
            it->second.setHeight(newHeight);
        }
    } else {
        throw std::runtime_error("Warehouse with given number does not exist");
    }
}

terminal::Terminal::~Terminal() {
    warehouses.clear();
}

terminal::Warehouse &terminal::Terminal::getWarehouse(int number) {
    auto it = warehouses.find(number);
    if (it != warehouses.end()) {
          return it->second;
    }
    else
        throw std::runtime_error("Warehouse with given number does not exist");
}


