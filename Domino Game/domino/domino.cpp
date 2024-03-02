#include <iostream>
#include "domino.h"

namespace lab2 {
    void Domino::displayAsciiArt() const {
        std::cout << "#######" << std::endl;
        std::cout << "#     #" << std::endl;
        std::cout << "#  " << end1 << "  #" << std::endl;
        std::cout << "#     #" << std::endl;
        std::cout << "#######" << std::endl;
        std::cout << "#     #" << std::endl;
        std::cout << "#  " << end2 << "  #" << std::endl;
        std::cout << "#     #" << std::endl;
        std::cout << "#######" << std::endl;
    }

    bool Domino::operator==(const Domino &domino) const {
        return (end1 == domino.end1 && end2 == domino.end2) || (end1 == domino.end2 && end2 == domino.end1);
    }

    Domino Domino::operator~() const {
        Domino domino(end2, end1);
        return domino;
    }

    std::ostream &operator<<(std::ostream &os, const Domino &domino) {
        os << domino.end1 << "|" << domino.end2;
        return os;
    }

    std::istream &operator>>(std::istream &is, Domino &domino) {
        domino.end1 = 0;
        domino.end2 = 0;
        is >> domino.end1 >> domino.end2;
        return is;
    }
}