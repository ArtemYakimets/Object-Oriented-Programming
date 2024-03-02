#ifndef LAB3_KDTREE_H
#define LAB3_KDTREE_H

#include <iostream>
#include <vector>
#include <stack>
#include <future>
//#include <algorithm>
//#include <execution>
#include "container.h"


namespace kdt {

    class KDTreeIterator;
    KDTreeIterator end();

    /**
    * @struct Point
    * @brief Represents a 3D point with x, y, and z coordinates.
    */
    struct Point {
        int x; /**< X coordinate */
        int y; /**< Y coordinate */
        int z; /**< Z coordinate */

        /**
        * @brief Default constructor.
        *
        * Initializes the point with coordinates (0, 0, 0).
        */
        Point() : x(0), y(0), z(0) {};


        /**
         * @brief Parameterized constructor.
         *
         * Initializes the point with the provided coordinates.
         *
         * @param x_ The x-coordinate.
         * @param y_ The y-coordinate.
         * @param z_ The z-coordinate.
         */
        Point(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {};

        /**
        * @brief Outputs the coordinates of the point to the output stream.
        * @param os The output stream to which the coordinates will be written.
        * @return The output stream containing the coordinates of the point.
        */
        std::ostream& print(std::ostream& os) const {
            os << "x: " << x << " y: " << y << " z: " << z << std::endl;
            return os;
        }
    };

    /**
    * @struct Node
    * @brief Represents a node in the KDTree.
    * @tparam T The type of space contained in the node.
    */
    template <class T>
    struct Node {
        std::shared_ptr<T> space; /**< Shared pointer to space */
        Node *left; /**< Pointer to the left child node */
        Node *right; /**< Pointer to the right child node */
        Node *par; /**< Pointer to the parent node */

        /**
        * @brief Explicit constructor for the Node.
        *
        * Initializes the Node with the provided space and sets the left, right, and parent pointers to nullptr.
        *
        * @param space_ The space to be stored in the node.
        */
        explicit Node(T space_): space(std::make_shared<T>(space_)), left(nullptr), right(nullptr), par(nullptr) {};
    };

    /**
    * @class KDTree
    * @brief Represents a KDTree that stores spaces of type T.
    * @tparam T The type of space to be stored in the KDTree.
    */
    template<class T>
    class KDTree {
    public:
        Node<T> *root; /**< Pointer to the root node of the KDTree */

        /**
         * @brief Default constructor for KDTree.
         *
         * Initializes the KDTree with the root node set to nullptr.
         */
        KDTree() : root(nullptr) {};

        /**
        * @brief Destructor for KDTree.
        *
        * Destroys the KDTree, deallocating all nodes and resources.
        * Calls the destroy function with the root node to free memory.
        */
        ~KDTree() { destroy(root); };

        /**
         * @brief Inserts a space into the KDTree structure.
         *
         * Inserts a space into the KDTree. If the KDTree is empty, the space becomes the root.
         * Otherwise, it finds the appropriate position based on median values of dimensions and inserts accordingly.
         *
         * @param space The space to be inserted into the KDTree.
         * @throw std::runtime_error If the container intersects with existing containers in the KDTree.
        */
        void insert(const T &space) {
            if (root == nullptr) {
                root = new Node(space);
                return;
            }

            std::vector<int> points;
            points = space.getCoordinates();

            Point min(points[0], points[1], points[2]);
            Point max(points[3], points[4], points[5]);

            if (!isEmpty(min, max))
                throw std::runtime_error("Container intersection: Unable to place the container.");


            int depth = 0;
            int flag;
            int cd;
            Node<T> *curr = root;
            Node<T> *par = nullptr;
            while (curr != nullptr) {
                cd = depth % 3;

                depth++;
                if (curr->space->getMedian()[cd] < space.getMedian()[cd]) {
                    par = curr;
                    curr = curr->left;
                    flag = 0;
                } else {
                    par = curr;
                    curr = curr->right;
                    flag = 1;
                }
            }

            if (flag == 0) {
                par->left = new Node(space);
                par->left->par = par;
            } else {
                par->right = new Node(space);
                par->right->par = par;
            }
        }

        /**
         * @brief Inserts a container space into the KDTree.
         *
         * Finds an appropriate space for the container within the KDTree based on available positions and dimensions.
         * Updates gravity and positions the container within the KDTree space.
         *
         * @param container The container to be inserted into the KDTree.
         * @param w_size The size of the KDTree space.
         * @throw std::runtime_error If unable to place the container due to intersection.
         */
        void insert(const terminal::Container &container, Point w_size) {
            T space = findInsertionPlace(container, w_size);

            std::vector<int> points;
            points = space.getCoordinates();

            Point min(points[0], points[1], points[2]);

            if (min.x == -1)
                throw std::runtime_error("Container intersection: Unable to place the container.");

            insert(space);
            updateGravity(space);
            updateGravityAbove(space, w_size.z);
        }

        /**
         * @brief Searches for a space in the KDTree by container number.
         *
         * Searches for a space within the KDTree based on the container number provided.
         *
         * @param number The container number to search for within the KDTree.
         * @return Node<T>* Pointer to the node containing the space with the specified container number.
         * @throw std::out_of_range If the container with the specified number is not found.
         */
        Node<T> *search(int number) {
            for (auto it = begin(); it != end(); ++it) {
                auto node = *it;
                if (number == node->space->getContainerNumber())
                    return node;
            }
            throw std::out_of_range("Container with specified number not found");
        }

        /**
         * @brief Prints the contents of the KDTree to the output stream.
         *
         * Prints the contents of the KDTree by iterating through each node and outputting the space details to the provided output stream.
         *
         * @param os The output stream where the KDTree contents will be printed.
         * @return std::ostream& A reference to the output stream after printing.
         */
        std::ostream &print(std::ostream &os) const {
            for (KDTreeIterator it = begin(); it != end(); ++it) {
                auto node = *it;
                node->space->print(os);
            }
            return os;
        }

        /**
         * @brief Replaces the position of a container in the KDTree.
         *
         * Replaces the position of a container identified by its number with a new minimum point (min) in the KDTree.
         * Updates the space's minimum and maximum points to place the container.
         *
         * @param number The number of the container to be replaced within the KDTree.
         * @param min The new minimum point for the container's position.
         * @throw std::runtime_error If unable to place the container due to intersection.
         */
        void replace(int number, Point min) {
            Node<T> *node = search(number);

            std::vector<int> size;
            size = node->space->getSize();

            int length = size[0];
            int width = size[1];
            int height = size[2];

            Point max(min.x + length, min.y + width, min.z + height);
            if (isEmpty(min, max)) {
                node->space->setMinPoint(min.x, min.y, min.z);
                node->space->setMaxPoint(max.x, max.y, max.z);
            } else
                throw std::runtime_error("Container intersection: Unable to place the container.");
        }

        /**
         * @brief Removes a container from the KDTree.
         *
         * Removes a container specified by its number from the KDTree.
         * Adjusts the tree structure accordingly by reassigning nodes.
         * Updates the positions of spaces above the removed container in the KDTree.
         *
         * @param number The number of the container to be removed from the KDTree.
         * @param max_height The maximum height of the KDTree space.
         */
        void remove(int number, int max_height) {

            Node<T> *node = search(number);

            Node<T> *par = node->par;

            if (node->right == nullptr) {
                if (par == nullptr) {
                    root = node->left;
                    if (root != nullptr)
                        root->par = par;
                } else if (node == par->left) {
                    par->left = node->left;
                    if (par->left != nullptr)
                        par->left->par = par;
                } else {
                    par->right = node->left;
                    if (par->right != nullptr)
                        par->right->par = par;
                }
            } else {
                Node<T> *right = node->right;
                if (right->left == nullptr) {
                    right->left = node->left;
                    if (right->left != nullptr)
                        right->left->par = right;

                    if (par == nullptr)
                        root = right;
                    else if (node == par->left)
                        par->left = right;
                    else
                        par->right = right;

                    right->par = par;
                } else {
                    Node<T> *succ = right->left;
                    while (succ->left != nullptr)
                        succ = succ->left;
                    right = succ->par;

                    right->left = succ->right;
                    if (right->left != nullptr)
                        right->left->par = right;

                    succ->left = node->left;
                    if (succ->left != nullptr)
                        succ->left->par = succ;

                    succ->right = node->right;
                    succ->right->par = succ;

                    if (par == nullptr)
                        root = succ;
                    else if (node == node->left)
                        par->left = succ;
                    else
                        par->right = succ;

                    succ->par = par;
                }
            }

            updateGravityAbove(*(node->space), max_height);
            delete node;
        }

    private:
        /**
        * @brief Checks if a space defined by the minimum and maximum points is empty within the KDTree.
        *
        * This function determines if the space, defined by the minimum and maximum points,
        * is empty within the KDTree structure.
        *
        * @param min The minimum point defining the space.
        * @param max The maximum point defining the space.
        * @return true if the space is empty, false otherwise.
        */
        bool isEmpty(Point min, Point max) { return isEmptyRec(root, min, max); }

        /**
        * @brief Recursively checks if a space defined by the minimum and maximum points is empty within a node.
        *
        * Recursively traverses the KDTree nodes to determine if the space, defined by the minimum and maximum points,
        * is empty within the specified node and its children.
        *
        * @param node The current node being checked for space emptiness.
        * @param min The minimum point defining the space.
        * @param max The maximum point defining the space.
        * @return true if the space is empty, false otherwise.
        */
        bool isEmptyRec(Node<T> *node, Point min, Point max) {
            if (node == nullptr)
                return true;

            std::vector<int> points;
            points = node->space->getCoordinates();

            Point curr_min(points[0], points[1], points[2]);
            Point curr_max(points[3], points[4], points[5]);

            if (!checkIntersection(curr_min, curr_max, min, max))
                return false;

            if (!isEmptyRec(node->left, min, max))
                return false;

            if (!isEmptyRec(node->right, min, max))
                return false;

            return true;
        }

        /**
        * @brief Checks for intersection between two spaces defined by their minimum and maximum points.
        *
        * Determines if two spaces, defined by their minimum and maximum points (A and B),
        * have an intersection or overlap.
        *
        * @param B_min The minimum point of space B.
        * @param B_max The maximum point of space B.
        * @param A_min The minimum point of space A.
        * @param A_max The maximum point of space A.
        * @return true if there is no intersection, false if there is an intersection.
        */
        bool checkIntersection(Point B_min, Point B_max, Point A_min, Point A_max) {
            if (A_min.x < B_max.x && A_max.x > B_min.x) {
                if (A_min.y < B_max.y && A_max.y > B_min.y) {
                    if (A_min.z < B_max.z && A_max.z > B_min.z) {
                        return false;
                    }
                }
            }

            return true;
        }

        /**
         * @brief Recursively destroys the KDTree.
         *
         * Deallocates memory by recursively traversing the tree
         * starting from the given node.
         *
         * @param node The root node of the tree to be destroyed.
         */
        void destroy(Node<T> *node) {
            if (node) {
                destroy(node->left);
                destroy(node->right);

                delete node;
            }
            root = nullptr;
        }

        /**
         * @brief Checks if the given coordinates are within specified bounds.
         *
         * Determines whether the provided minimum and maximum points fall within the bounds of the specified size.
         *
         * @param min The minimum coordinate point.
         * @param max The maximum coordinate point.
         * @param w_size The size indicating the maximum bounds.
         * @return true if the coordinates are within bounds, false otherwise.
         */
        bool isInsideBounds(Point min, Point max, Point w_size) {
            if (min.x < 0 || min.y < 0 || min.z < 0)
                return false;

            if (max.x > w_size.x || max.y > w_size.y || max.z > w_size.z)
                return false;

            return true;
        }

        /**
         * @brief Finds an appropriate insertion place for a container within the KDTree.
         *
         * Attempts to find a suitable space to insert a container within the KDTree, based on available space.
         *
         * @param container The container to be inserted.
         * @param w_size The size indicating the maximum bounds of the space.
         * @return T The coordinates of the insertion place and the container information.
         */
        T findInsertionPlace(terminal::Container container, Point w_size) {
            std::mutex containerMutex;

            if (root == nullptr)
                return {0, 0, 0, container.getLength(), container.getWidth(), container.getHeight(), container};

            std::vector<std::future<T>> futures;

            for (auto it = begin(); it != end(); ++it) {
                auto node = *it;

                futures.push_back(std::async(std::launch::async, [this, node, &container, w_size, &containerMutex]() -> T {
                    std::vector<int> points;
                    points = node->space->getCoordinates();

                    Point curr_min(points[0], points[1], points[2]);
                    Point curr_max(points[3], points[4], points[5]);

                    for (int i = 0; i < 3; i++) {
                        int length = container.getLength();
                        int width = container.getWidth();
                        int height = container.getHeight();

                        // 1
                        Point min(curr_max.x - length, curr_max.y, curr_min.z);
                        Point max(min.x + length, min.y + width, min.z + height);
                        if (isInsideBounds(min, max, w_size)) {
                            if (isEmpty(min, max))
                                return {min.x, min.y, min.z, max.x, max.y, max.z, container};
                        }

                        //2
                        min.x = curr_max.x;
                        min.y = curr_max.y - width;
                        min.z = curr_min.z;
                        max.x = min.x + length;
                        max.y = min.y + width;
                        max.z = min.z + height;
                        if (isInsideBounds(min, max, w_size)) {
                            if (isEmpty(min, max))
                                return {min.x, min.y, min.z, max.x, max.y, max.z, container};
                        }

                        //3
                        max.x = curr_max.x;
                        max.y = curr_min.y;
                        max.z = curr_max.z;
                        min.x = max.x - length;
                        min.y = max.y - width;
                        min.z = max.z - height;
                        if (isInsideBounds(min, max, w_size)) {
                            if (isEmpty(min, max))
                                return {min.x, min.y, min.z, max.x, max.y, max.z, container};
                        }

                        //4
                        max.x = curr_min.x;
                        max.y = curr_max.y;
                        max.z = curr_max.z;
                        min.x = max.x - length;
                        min.y = max.y - width;
                        min.z = max.z - height;
                        if (isInsideBounds(min, max, w_size)) {
                            if (isEmpty(min, max))
                                return {min.x, min.y, min.z, max.x, max.y, max.z, container};
                        }

                        //5
                        min.x = curr_min.x;
                        min.y = curr_min.y;
                        min.z = curr_max.z;
                        max.x = min.x + length;
                        max.y = min.y + width;
                        max.z = min.z + height;
                        if (isInsideBounds(min, max, w_size)) {
                            if (isEmpty(min, max))
                                return {min.x, min.y, min.z, max.x, max.y, max.z, container};
                        }

                        //6
                        max.x = curr_max.x;
                        max.y = curr_max.y;
                        max.z = curr_min.z;
                        min.x = max.x - length;
                        min.y = max.y - width;
                        min.z = max.z - height;
                        if (isInsideBounds(min, max, w_size)) {
                            if (isEmpty(min, max))
                                return {min.x, min.y, min.z, max.x, max.y, max.z, container};
                        }

                        std::lock_guard<std::mutex> lock(containerMutex);
                        if (container.getType() == "CHILLED" || container.getType() == "REGULAR")
                            container.rotate(i + 1);
                        else
                            break;
                    }

                    return {-1, -1, -1, -1, -1, -1, container};

                }));
            }

            // Wait for all threads to finish and collect results
            for (auto& future : futures) {
                T result = future.get();
                std::vector<int> coordinates = result.getCoordinates();
                if (coordinates[0] != -1) {
                    return result; // Return the first successful result
                }
            }

            return {-1, -1, -1, -1, -1, -1, container};
        }

        /**
         * @brief Updates the gravity of a space within the KDTree.
         *
         * Updates the gravity of the specified space by adjusting its coordinates.
         *
         * @param space The space for which gravity needs to be updated.
         */
        void updateGravity(T &space) {

            std::vector<int> points;
            points = space.getCoordinates();

            Point curr_min(points[0], points[1], points[2]);
            Point curr_max(points[3], points[4], points[5]);

            Point min(curr_min.x, curr_min.y, curr_min.z - 1);
            Point max(curr_max.x, curr_max.y, curr_min.z);

            while (isEmpty(min, max) && min.z >= 0) {
                space.setMinPoint(curr_min.x, curr_min.y, curr_min.z - 1);
                space.setMaxPoint(curr_max.x, curr_max.y, curr_max.z - 1);
                min.z -= 1;
                max.z -= 1;
            }
        }

        /**
         * @brief Updates the gravity of spaces above a specified space within the KDTree.
         *
         * Updates the gravity of spaces positioned above the given space within the KDTree.
         *
         * @param space The space for which gravity above needs to be updated.
         * @param max_height The maximum height value.
         */
        void updateGravityAbove(T &space, int max_height) {

            std::vector<int> points;
            points = space.getCoordinates();

            Point curr_min(points[0], points[1], points[2]);
            Point curr_max(points[3], points[4], points[5]);

            Point min(curr_min.x, curr_min.y, curr_max.z);
            Point max(curr_max.x, curr_max.y, max_height);
            for (auto it = begin(); it != end(); ++it) {
                Node<T> *node = *it;
                if (checkIntersection(curr_min, curr_max, min, max))
                    updateGravity(*(node->space));
            }
        }

        /**
        * @brief Iterator for traversing the nodes of a KDTree.
        *
        * This iterator allows traversal of nodes within a KDTree structure.
        * It enables operations like accessing nodes, moving to the next node,
        * and checking for inequality between iterators.
        *
        * @tparam T The type of the Node elements being iterated over.
         */
        class KDTreeIterator {
        private:
            Node<T> *curr; /**< Current node being pointed to by the iterator. */
            std::stack<Node<T>*> stack; /**< Stack to maintain the traversal path. */

            /**
             * @brief Populates the stack with nodes for traversal.
             *
             * @param node The starting node for populating the stack.
             */
            void populateStack(Node<T> *node) {
                while (node != nullptr) {
                    stack.push(node);
                    node = node->left;
                }
            }

        public:
            /**
             * @brief Constructs an iterator starting at the specified root node.
             *
             * Initializes the iterator starting at the given root node
             * and populates the stack for traversal.
             *
             * @param root The root node of the KDTree.
             */
            explicit KDTreeIterator(Node<T> *root) {
                curr = root;
                populateStack(curr);
            }

            /**
             * @brief Dereferences the iterator to access the current node.
             *
             * @return Node<T>* The pointer to the current node.
             */
            Node<T> *operator*() {
                return stack.top();
            }

            /**
             * @brief Moves the iterator to the next node in the traversal order.
             */
            void operator++() {
                Node<T> *current = stack.top()->right;
                stack.pop();

                while (current != nullptr) {
                    stack.push(current);
                    current = current->left;
                }
            }

            /**
             * @brief Checks for inequality between iterators.
             *
             * @param other The iterator to compare with.
             * @return true if the iterators are not equal, false otherwise.
             */
            bool operator!=(const KDTreeIterator& other) const {
                return !stack.empty() || !other.stack.empty();
            }
        };

        /**
        * @brief Gets the iterator pointing to the beginning of the KDTree.
        * @return The iterator pointing to the beginning.
        */
        KDTreeIterator begin() const {
            return KDTreeIterator(root);
        }

        /**
         * @brief Gets the iterator pointing to the end of the KDTree.
         * @return The iterator pointing to the end.
         */
        KDTreeIterator end() const {
            return KDTreeIterator(nullptr);
        }
    };
}
#endif //LAB3_KDTREE_H
