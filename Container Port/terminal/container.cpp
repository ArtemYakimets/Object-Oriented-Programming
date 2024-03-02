#include "container.h"

#include <utility>
#include <iostream>
#include <vector>

namespace terminal {
    Container::Container() {
        number = 0;
        name = "untitled";
        length = 1;
        width = 1;
        height = 1;
        weight = 1;
        cost = 0;
    }

    Container::Container(int number, std::string name, double length, double width, double height,
                         double weight, double cost) {
        this->number = number;
        this->name = std::move(name);
        this->length = length;
        this->width = width;
        this->height = height;
        this->weight = weight;
        this->cost = cost;
    }
//
//    void Container::print() {
//        std::cout << "### CONTAINER ###" << std::endl;
//        std::cout << "number: "  << number << std::endl;
//        std::cout << "name: "  << name << std::endl;
//        std::cout << "length: "  << length << std::endl;
//        std::cout << "width: "  << width << std::endl;
//        std::cout << "height: "  << height << std::endl;
//        std::cout << "weight: "  << weight << std::endl;
//        std::cout << "cost: $"  << cost << std::endl;
//        std::cout << "#################" << std::endl;
//    }

    void Container::rotate(int axis) {
        if (axis == 1) { // Поворот по оси x
            int temp = length;
            length = height;
            height = temp;
        } else if (axis == 2) { // Поворот по оси y
            int temp = width;
            width = height;
            height = temp;
        } else if (axis == 3) { // Поворот по оси z
            int temp = length;
            length = width;
            width = temp;
        } else {
            throw std::invalid_argument("Invalid axis number");
        }
    }

    std::ostream &Container::print(std::ostream &os) const {
        os << "### CONTAINER ###" << std::endl;
        os << "number: "  << number << std::endl;
        os << "name: "  << name << std::endl;
        os << "length: "  << length << std::endl;
        os << "width: "  << width << std::endl;
        os << "height: "  << height << std::endl;
        os << "weight: "  << weight << std::endl;
        os << "cost: $"  << cost << std::endl;
        os << "#################" << std::endl;
        return os;
    }


    FragileContainer::FragileContainer() {
        number = 0;
        name = "untitled";
        length = 1;
        width = 1;
        height = 1;
        weight = 1;
        cost = 0;
        max_weight = 0;
    }

    FragileContainer::FragileContainer(int number, std::string name, double length, double width, double height,
                                       double weight, double cost, double max_weight) {
        this->number = number;
        this->name = std::move(name);
        this->length = length;
        this->width = width;
        this->height = height;
        this->weight = weight;
        this->cost = cost;
        this->max_weight = max_weight;
    }

    std::ostream &FragileContainer::print(std::ostream &os) const {
        Container::print(os);
        os << "max weight: " << max_weight << std::endl;
        return os;
    }


    ChilledContainer::ChilledContainer() {
        number = 0;
        name = "untitled";
        length = 1;
        width = 1;
        height = 1;
        weight = 1;
        cost = 0;
        temperature = 0;
    }

    ChilledContainer::ChilledContainer(int number, std::string name, double length, double width, double height,
                                       double weight, double cost, double temperature) {
        this->number = number;
        this->name = std::move(name);
        this->length = length;
        this->width = width;
        this->height = height;
        this->weight = weight;
        this->cost = cost;
        this->temperature = temperature;
    }

    std::ostream &ChilledContainer::print(std::ostream &os) const {
        Container::print(os);
        os << "temperature: " << temperature << std::endl;
        return os;
    }

    FragileChilledContainer::FragileChilledContainer() {
        FragileContainer::number = 0;
        FragileContainer::name = "untitled";
        FragileContainer::length = 1;
        FragileContainer::width = 1;
        FragileContainer::height = 1;
        FragileContainer::weight = 1;
        FragileContainer::cost = 0;
        temperature = 0;
        max_weight = 0;
    }

    FragileChilledContainer::FragileChilledContainer(int number, std::string name, double length, double width,
                                                     double height, double weight, double cost, double temperature,
                                                     double max_weight) {
        this->FragileContainer::number = number;
        this->FragileContainer::name = std::move(name);
        this->FragileContainer::length = length;
        this->FragileContainer::width = width;
        this->FragileContainer::height = height;
        this->FragileContainer::weight = weight;
        this->FragileContainer::cost = cost;
        this->temperature = temperature;
        this->max_weight = max_weight;
    }

    std::ostream &FragileChilledContainer::print(std::ostream &os) const {
        ChilledContainer::print(os);
        os << "temperature: " << temperature << std::endl;
        os << "max weight: " << max_weight << std::endl;
        return os;
    }

    terminal::Point::Point(int x_, int y_, int z_) {
        x = x_;
        y = y_;
        z = z_;
    }

    std::ostream &terminal::Point::print(std::ostream &os) const {
        os << "x: " << x << " y: " << y << " z: " << z << std::endl;
        return os;
    }

    terminal::ContainerSpace::ContainerSpace(int minX, int minY, int minZ, int maxX, int maxY, int maxZ, const terminal::Container& c)
            : min(minX, minY, minZ), max(maxX, maxY, maxZ), container(std::make_shared<terminal::Container>(c)) {
    }


    std::vector<int> terminal::ContainerSpace::getMedian() const {
        int medianX = (min.x + max.x) / 2;
        int medianY = (min.y + max.y) / 2;
        int medianZ = (min.z + max.z) / 2;
        std::vector<int> coords = {medianX, medianY, medianZ};
        return coords;
    }

    std::vector<int> ContainerSpace::getCoordinates() const{
        std::vector<int> coordinates;
        coordinates.push_back(min.x);
        coordinates.push_back(min.y);
        coordinates.push_back(min.z);
        coordinates.push_back(max.x);
        coordinates.push_back(max.y);
        coordinates.push_back(max.z);
        return coordinates;
    }

    std::ostream &ContainerSpace::print(std::ostream &os) const {
        container->print(os);
        os << "Min: (" << min.x << "; " << min.y << "; " << min.z << ")" << std::endl;
        os << "Max: (" << max.x << "; " << max.y << "; " << max.z << ")" << std::endl;
        return os;
    }

    std::vector<int> ContainerSpace::getSize() const {
        std::vector<int> size;
        size.push_back(container->getLength());
        size.push_back(container->getWidth());
        size.push_back(container->getHeight());
        return size;
    }
}