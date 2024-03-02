#ifndef LAB3_CONTAINER_H
#define LAB3_CONTAINER_H

#include <string>
#include <vector>
#include <memory>

namespace terminal {

    class Container {
    protected:
        int number;
        std::string name;
        double length;
        double width;
        double height;
        double weight;
        double cost;
    public:
        Container();
        Container(int number, std::string name, double length, double width, double height,
                  double weight, double cost);

        [[nodiscard]] int getNumber() const { return number; }
        [[nodiscard]] std::string getName() const { return name; }
        [[nodiscard]] double getLength() const { return length; }
        [[nodiscard]] double getWidth() const { return width; }
        [[nodiscard]] double getHeight() const { return height; }
        [[nodiscard]] double getWeight() const { return weight; }
        [[nodiscard]] double getCost() const { return cost; }
        [[nodiscard]] virtual std::string getType() const { return "REGULAR"; }

        void setNumber(int newNumber) { number = newNumber; }
        void setName(const std::string& newName) { name = newName; }
        void setLength(double newLength) { length = newLength; }
        void setWidth(double newWidth) { width = newWidth; }
        void setHeight(double newHeight) { height = newHeight; }
        void setWeight(double newWeight) { weight = newWeight; }
        void setCost(double newCost) { cost = newCost; }

        void rotate(int axis);
        virtual std::ostream& print(std::ostream& os) const;

        virtual ~Container() = default;
    };

    class ChilledContainer : virtual public Container {
    protected:
        double temperature;
    public:
        ChilledContainer();
        ChilledContainer(int number, std::string name, double length, double width, double height,
                         double weight, double cost, double temperature);

        [[nodiscard]] double getTemperature() const { return temperature; }
        [[nodiscard]] std::string getType() const override { return "CHILLED"; }

        std::ostream& print(std::ostream& os) const override;
        void setTemperature(double newTemperature) { temperature = newTemperature; }
    };

    class FragileContainer : virtual public Container {
    protected:
        double max_weight;
    public:
        FragileContainer();
        FragileContainer(int number, std::string name, double length, double width, double height,
                  double weight, double cost, double max_weight);

        [[nodiscard]] double getMaxWeight() const { return max_weight; }
        [[nodiscard]] std::string getType() const override { return "FRAGILE"; }

        std::ostream& print(std::ostream& os) const override;
        void setMaxWeight(double newMaxWeight) { max_weight = newMaxWeight; }
    };

    class FragileChilledContainer : public FragileContainer, public ChilledContainer {
    public:
        FragileChilledContainer();
        FragileChilledContainer(int number, std::string name, double length, double width, double height,
                         double weight, double cost, double temperature, double max_weight);

        std::ostream& print(std::ostream& os) const override;
        [[nodiscard]] std::string getType() const override { return "FRAGILE_CHILLED"; }
    };

    struct Point {
        int x;
        int y;
        int z;

        Point() : x(0), y(0), z(0) {};
        Point(int x_, int y_, int z_);
        std::ostream& print(std::ostream& os) const;
    };

    class ContainerSpace {
    private:
        Point min;
        Point max;
        std::shared_ptr<terminal::Container> container;

    public:
        ContainerSpace(int minX, int minY, int minZ, int maxX, int maxY, int maxZ, const terminal::Container& c);

        void setMinPoint(int x, int y, int z) { min.x = x; min.y = y; min.z = z; }
        void setMaxPoint(int x, int y, int z) { max.x = x; max.y = y; max.z = z; }

        [[nodiscard]] std::vector<int> getMedian() const;
        [[nodiscard]] int getContainerNumber() const { return container->getNumber(); }
        [[nodiscard]] std::vector<int> getCoordinates() const;
        [[nodiscard]] std::vector<int> getSize() const;

        std::ostream& print(std::ostream& os) const;
    };
}
#endif //LAB3_CONTAINER_H
