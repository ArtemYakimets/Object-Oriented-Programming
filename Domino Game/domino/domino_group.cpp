#include <iostream>
#include "domino_group.h"

namespace lab2 {

    void DominoGroup::expandCapacity() {
        capacity *= 2;
        auto *newDominoes = new Domino[capacity];
        for (int i = 0; i < size; i++)
            newDominoes[i] = dominoes[i];

        delete[] dominoes;
        dominoes = newDominoes;
    }

    DominoGroup & DominoGroup::operator+=(const Domino &domino) {
        if (size >= capacity)
            expandCapacity();
        dominoes[size++] = domino;
        return *this;
    }

    DominoGroup & DominoGroup::operator=(const DominoGroup &other) {
        if (this != &other) {
            auto *bones = new Domino[capacity];
            size = other.size;
            capacity = other.capacity;
            delete[] dominoes;
            dominoes = bones;
            std::copy(other.dominoes, other.dominoes + other.size, dominoes);
        }
        return *this;
    }

    DominoGroup & DominoGroup::operator=(DominoGroup &&other) noexcept {
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
        std::swap(dominoes, other.dominoes);
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const DominoGroup& group) {
        for (int i = 0; i < group.size; i++) {
            os << group.dominoes[i].getEnd1() << "|" << group.dominoes[i].getEnd2() << " ";
            if ((i + 1) % 10 == 0)
                os << std::endl;
        }
        os << std::endl;
        return os;
    }

    std::istream& operator>>(std::istream& is, lab2::DominoGroup& group) {
        group.clear();

        int numBones;
        is >> numBones;

        if (is.fail() || numBones < 0) {
            is.setstate(std::ios::failbit);
            return is;
        }

        for (int i = 0; i < numBones; ++i) {
            int end1, end2;
            is >> end1 >> end2;

            if (is.fail()) {
                is.setstate(std::ios::failbit);
                return is;
            }

            lab2::Domino domino(end1, end2);
            group.addDomino(domino);
        }

        return is;
    }


    DominoGroup DominoGroup::createRandomGroup(int cp) {
        std::vector<Domino> bones;
        for (int i = 0; i < cp; i++) {
            Domino bone = Domino::createRandomDomino();
            bones.push_back(bone);
        }
        return DominoGroup(bones);
    }

    DominoGroup DominoGroup::createGroupWithAllTypes(int num) {
        std::vector<Domino> bones;
        for (int i = 0; i < num; i++) {
            for (int end1 = 1; end1 < 7; end1++) {
                for (int end2 = 1; end2 < 7; end2++) {
                    Domino bone(end1, end2);
                    bones.push_back(bone);
                }
            }
        }
        return DominoGroup(bones);
    }

    void DominoGroup::addDomino(const Domino &domino) {
        if (size >= capacity)
            expandCapacity();
        dominoes[size++] = domino;
    }

    Domino DominoGroup::removeDomino(const Domino &domino) {
        if (size <= 0)
            throw std::out_of_range("The group is empty!");

        for (int i = 0; i < size; i++) {
            if (dominoes[i] == domino) {
                Domino bone = dominoes[i];
                //for (int j = i; j < size - 1; j++)
                //    dominoes[j] = dominoes[j + 1];
                dominoes[i] = dominoes[size - 1];
                size--;
                return bone;
            }
        }
        throw std::out_of_range("Index out of range!");
    }

    Domino DominoGroup::removeDominoByIndex(int index) {
        if (index > size - 1 || index < 0)
            throw std::out_of_range("Index out of range!");

        Domino bone = dominoes[index];
        //for (int i = index; i < size - 1; i++)
        //    dominoes[i] = dominoes[i + 1];
        dominoes[index] = dominoes[size - 1];

        size--;
        return bone;
    }

    void DominoGroup::clear() {
        delete[] dominoes;
        dominoes = new Domino[capacity];
        size = 0;
        capacity = 10;
    }

    const Domino &DominoGroup::operator[](int index) {
        if (index >= 0 && index < size)
            return dominoes[index];

        throw std::out_of_range("Index out of range!");
    }

    void DominoGroup::sortBySumAscending() {
        if (size <= 0)
            throw std::out_of_range("The group is empty!");

        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (dominoes[j].getSum() > dominoes[j + 1].getSum()) {
                    Domino tmp = dominoes[j];
                    dominoes[j] = dominoes[j + 1];
                    dominoes[j + 1] = tmp;
                }
            }
        }
    }

    DominoGroup DominoGroup::extractSubgroup(int value) {
        if (size <= 0)
            throw std::out_of_range("The group is empty!");

        DominoGroup subgroup;
        for (int i = 0; i < size; i++) {
            if (dominoes[i].getEnd1() == value || dominoes[i].getEnd2() == value) {
                subgroup += dominoes[i];
                removeDominoByIndex(i);
                i--;
            }
        }
        return subgroup;
    }

    void DominoGroup::print() {
        if (size <= 0)
            throw std::out_of_range("The group is empty!");

        for (int i = 0; i < size; i++) {
            std::cout << dominoes[i].getEnd1() << "|" << dominoes[i].getEnd2() << " ";
            if ((i + 1) % 10 == 0)
                std::cout << std::endl;
        }
        std::cout << std::endl;
    }

}
