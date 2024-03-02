#include <stdexcept>
#include "warehouse.h"

terminal::Warehouse::Warehouse() {
    temperature = 20;
    length = 100;
    width = 100;
    height = 20;
    containers = kdt::KDTree<ContainerSpace>();
}

terminal::Warehouse::Warehouse(double temperature_, double length_, double width_, double height_) {
    temperature = temperature_;
    length = length_;
    width = width_;
    height = height_;
    containers = kdt::KDTree<ContainerSpace>();
}

void terminal::Warehouse::insertContainerWithCoordinates(const ContainerSpace& cs) {
    std::vector<int> points;
    points = cs.getCoordinates();

    Point min(points[0], points[1], points[2]);
    Point max(points[3], points[4], points[5]);

    if (max.x > length || max.y > width || max.z > height)
        throw std::runtime_error("The coordinates are out of bounds");
    containers.insert(cs);
}

void terminal::Warehouse::replaceContainer(int number, const ContainerSpace& cs) {
    std::vector<int> points;
    points = cs.getCoordinates();

    kdt::Point min(points[0], points[1], points[2]);
    kdt::Point max(points[3], points[4], points[5]);

    if (max.x > length || max.y > width || max.z > height)
        throw std::runtime_error("The coordinates are out of bounds");
    containers.replace(number, min);
}

void terminal::Warehouse::removeContainer(int number) {
    containers.remove(number, height);
}

std::ostream &terminal::Warehouse::print(std::ostream &os) {
    return containers.print(os);
}

void terminal::Warehouse::insertContainer(const terminal::Container& c) {
    kdt::Point w_size(length, width, height);
    containers.insert(c, w_size);
}

int terminal::Warehouse::getMaxNumberOfContainers(const terminal::Container& c) {
    int max = (length * width * height) / (c.getHeight() * c.getWidth() * c.getLength());
    return max;
}

void terminal::Warehouse::showContainer(int number) {
    containers.search(number)->space->print(std::cout);
}

void terminal::Warehouse::addDefaultContainer() {
    Container c(1, "a", 1, 1, 1, 1, 1);
    kdt::Point w_size(length, width, height);
    containers.insert(c, w_size);
}


