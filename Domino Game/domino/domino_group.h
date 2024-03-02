#ifndef LAB2A_DOMINO_GROUP_H
#define LAB2A_DOMINO_GROUP_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include "domino.h"

namespace lab2 {

    class DominoGroup {
    private:
        /**
         * @class DominoGroup
         * @brief Represents a group of dominoes with various operations.
         *
         * This class represents a group of dominoes and provides methods for manipulating them.
         * Dominoes can be added, removed, sorted, and subgroups can be extracted based on specific values.
         */
        Domino *dominoes; ///< An array of dominoes.
        int size;         ///< The current number of dominoes in the group.
        int capacity;     ///< The maximum capacity of the group.

        /**
         * @brief Expands the capacity of the DominoGroup when necessary.
         */
        void expandCapacity();
    public:
        /**
         * @brief Default constructor.
         *
         * Creates an empty DominoGroup with a default capacity of 10.
         */
        DominoGroup(): size(0), capacity(10) { dominoes = new Domino[capacity]; }

        /**
         * @brief Explicit constructor with capacity.
         *
         * Creates an empty DominoGroup with the specified capacity.
         *
         * @param cp The capacity of the DominoGroup.
         */
        explicit DominoGroup(int cp): size(cp), capacity(cp) { dominoes = new Domino[capacity]; }

        /**
         * @brief Constructor with a vector of dominoes.
         *
         * Creates a DominoGroup from a vector of dominoes.
         *
         * @param bones A vector containing dominoes.
         */
        explicit DominoGroup(const std::vector<Domino> &bones): size(bones.size()), capacity(size) {
            dominoes = new Domino[capacity];
            for (int i = 0; i < size; i++)
                dominoes[i] = bones[i];
        }

        /**
         * @brief Copy constructor.
         *
         * Creates a new DominoGroup by copying another DominoGroup.
         *
         * @param other The DominoGroup to copy from.
         */
        DominoGroup(const DominoGroup& other) : size(other.size), capacity(other.capacity) {
            dominoes = new Domino[capacity];
            std::copy(other.dominoes, other.dominoes + other.size, dominoes);
        }

        /**
         * @brief Move constructor.
         *
         * Creates a new DominoGroup by moving the content of another DominoGroup.
         *
         * @param other The DominoGroup to move from.
         */
        DominoGroup(DominoGroup&& other) noexcept: dominoes(other.dominoes), size(other.size), capacity(other.capacity) {
            other.dominoes = nullptr;
        }

        /**
         * @brief Destructor.
         *
         * Destroys the DominoGroup and frees memory.
         */
        ~DominoGroup() { delete[] dominoes; }

        /**
         * @brief Sets the capacity of the DominoGroup.
         *
         * @param cp The new capacity of the DominoGroup.
         */
        void setCapacity(int cp) { capacity = cp; }

        /**
         * @brief Sets the size of the DominoGroup.
         *
         * @param sz The new size of the DominoGroup.
         */
        void setSize(int sz) { size = sz; }

        /**
         * @brief Gets the capacity of the DominoGroup.
         *
         * @return The current capacity of the DominoGroup.
         */
        int getCapacity() const { return capacity; }

        /**
         * @brief Gets the size of the DominoGroup.
         *
         * @return The current size of the DominoGroup.
         */
        int getSize() const { return size; }

        /**
         * @brief Adds a domino to the group.
         *
         * @param domino The domino to add.
         * @return A reference to the updated DominoGroup.
         */
        DominoGroup & operator+=(const Domino &domino);

        /**
         * @brief Accesses a domino in the group by index.
         *
         * @param index The index of the domino to access.
         * @return A reference to the domino at the specified index.
         */
        const Domino& operator[](int index);


        /**
         * @brief Copy assignment operator.
         *
         * Assigns the content of another DominoGroup by copying.
         *
         * @param group The DominoGroup to copy from.
         * @return A reference to the updated DominoGroup.
         */
        DominoGroup & operator=(const DominoGroup &group);

        /**
         * @brief Move assignment operator.
         *
         * Assigns the content of another DominoGroup by moving.
         *
         * @param other The DominoGroup to move from.
         * @return A reference to the updated DominoGroup.
         */
        DominoGroup & operator=(DominoGroup &&other) noexcept;

/**
 * @brief The output operator for the Domino Group class.
 *
 * This operator allows you to output the contents of the Domino Group object to the output stream.
 *
 * @param os - the output stream to which the DominoGroup object will be written.
 * @param group - the Domino Group object to output.
 * @return Link to the output stream after the DominoGroup output.
 */
        friend std::ostream& operator<<(std::ostream& os , const DominoGroup &group);

        /**
 * @brief Input operator for the DominoGroup class.
 *
 * This operator allows you to read the contents of the Domino Group object from the input stream.
 *
 * @param is - This operator allows you to read the contents of the Domino Group object from the input stream.
 * @param group - the Domino Group object to which the input will be read.
 * @return Link to the input stream after reading DominoGroup.
 */
        friend std::istream & operator>>(std::istream &is, DominoGroup &group);

        /**
         * @brief Generates a random DominoGroup with the specified capacity.
         *
         * @param cp The capacity of the random DominoGroup.
         * @return A random DominoGroup.
         */
        static DominoGroup createRandomGroup(int cp);

        /**
         * @brief Generates a DominoGroup with all possible domino types up to a given number.
         *
         * @param num The maximum domino value to include in the group.
         * @return A DominoGroup with all possible domino types up to the specified value.
         */
        static DominoGroup createGroupWithAllTypes(int num);

        /**
         * @brief Adds a domino to the group.
         *
         * @param domino The domino to add.
         */
        void addDomino(const Domino &domino);

        /**
         * @brief Removes a specific domino from the group.
         *
         * @param domino The domino to remove.
         * @return The removed domino.
         */
        Domino removeDomino(const Domino &domino);

        /**
         * @brief Removes a domino from the group by its index.
         *
         * @param index The index of the domino to remove.
         * @return The removed domino.
         */
        Domino removeDominoByIndex(int index);

        /**
         * @brief Clears the DominoGroup, removing all dominoes.
         */
        void clear();

        /**
         * @brief Sorts the dominoes in the group by the sum of their values in ascending order.
         */
        void sortBySumAscending();

        /**
         * @brief Extracts a subgroup of dominoes containing a specific value.
         *
         * @param value The value to search for in the dominoes.
         * @return A new DominoGroup containing the matching dominoes.
         */
        DominoGroup extractSubgroup(int value);

        /**
         * @brief Prints the DominoGroup to the standard output.
         */
        void print();
    };
}


#endif //LAB2A_DOMINO_GROUP_H
