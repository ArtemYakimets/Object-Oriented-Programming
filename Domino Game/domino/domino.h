#ifndef LAB2A_DOMINO_H
#define LAB2A_DOMINO_H

#include <cstdlib>
#include <iostream>
#include <vector>

namespace lab2 {
    /**
    * @brief A class representing a domino tile with two numeric values (ends).
    */
    class Domino {
    private:
        int end1; /**< The value of the first end of the domino. */
        int end2; /**< The value of the second end of the domino. */


    public:
        /**
        * @brief Default constructor.
        *
        * Creates a domino with both ends initialized to 0.
        */
        Domino(): end1(0), end2(0) {}

        /**
        * @brief Constructor with specific values for ends.
        *
        * Creates a domino with the specified values for its ends.
        *
        * @param value1 The value of the first end.
        * @param value2 The value of the second end.
        */
        Domino(int value1, int value2): end1(value1), end2(value2) {}

        /**
        * @brief Generates a random domino.
        *
        * Creates a domino with random values between 1 and 6 for both ends.
        *
        * @return A randomly generated domino.
        */
        static Domino createRandomDomino() {
            int a = 1 + rand() % 6;
            int b = 1 + rand() % 6;
            return Domino(a, b);
        }

        /**
        * @brief Checks if two dominoes are equal.
        *
        * Two dominoes are considered equal if they have the same values on their ends,
        * regardless of their order.
        *
        * @param domino The domino to compare with.
        * @return `true` if the dominoes are equal, `false` otherwise.
        */
        bool operator==(const Domino &domino) const;

        /**
        * @brief Creates a new domino by swapping the values of ends.
        *
        * @return A new domino with the values of its ends swapped.
        */
        Domino operator~() const;

        /**
        * @brief Outputs the domino to an output stream.
        *
        * @param os The output stream.
        * @param domino The domino to output.
        * @return The output stream.
        */
        friend std::ostream& operator<<(std::ostream& os , const Domino &domino);

        /**
 * @brief Inputs a domino from an input stream.
 *
 * @param is The input stream.
 * @param domino The domino to input.
 * @return The input stream.
 */
        friend std::istream & operator>>(std::istream &is, Domino &domino);

        /**
 * @brief Sets the values of both ends.
 *
 * @param a The value for the first end.
 * @param b The value for the second end.
 */
        void setEnds(int a, int b) {
            this->end1 = a;
            this->end2 = b;
        }

        /**
 * @brief Gets the value of the first end.
 *
 * @return The value of the first end.
 */
        int getEnd1() const { return end1; }

        /**
 * @brief Gets the value of the second end.
 *
 * @return The value of the second end.
 */
        int getEnd2() const { return end2; }

        /**
 * @brief Calculates the sum of the values on both ends.
 *
 * @return The sum of the values on both ends.
 */
        int getSum() const { return (end1 + end2); }

        /**
         * @brief Displays the domino as ASCII art on the standard output.
         */
        void displayAsciiArt() const;
    };
}
#endif //LAB2A_DOMINO_H
