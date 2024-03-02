#ifndef LAB3_WAREHOUSE_H
#define LAB3_WAREHOUSE_H

#include <exception>
#include "container.h"
#include "kdtree.h"

namespace terminal {

    class Warehouse {
    private:
        double temperature;
        double length;
        double width;
        double height;
        kdt::KDTree<ContainerSpace> containers;
    public:
        Warehouse();
        Warehouse(double temperature_, double length_, double width_, double height_);

        [[nodiscard]] double getTemperature() const { return temperature; }
        [[nodiscard]] double getLength() const { return length; }
        [[nodiscard]] double getWidth() const { return width; }
        [[nodiscard]] double getHeight() const { return height; }

        void setTemperature(double temperature_) { temperature = temperature_;}
        void setLength(double length_) { length = length_; }
        void setWidth(double width_) { width = width_; }
        void setHeight(double height_) { height = height_; }

        void insertContainerWithCoordinates(const ContainerSpace& cs);
        void replaceContainer(int number, const ContainerSpace& cs);
        void removeContainer(int number);
        std::ostream &print(std::ostream &os);
        void insertContainer(const Container& c);
        int getMaxNumberOfContainers(const Container& c);
        void showContainer(int number);
        void addDefaultContainer();

    };
}
#endif //LAB3_WAREHOUSE_H
