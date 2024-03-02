#include <catch2/catch_all.hpp>
#include "../terminal/container.h"
#include "../terminal/kdtree.h"

TEST_CASE("KDTree testing") {
    kdt::KDTree<terminal::ContainerSpace> tree;

    SECTION("Insertion automatically") {
        kdt::Point w_size(2, 2, 2);

        terminal::Container c1(1, "a", 1, 1, 1, 10, 10);
        tree.insert(c1, w_size);

        REQUIRE(tree.search(1) != nullptr);

        terminal::Container c2(2, "a", 1, 1, 1, 10, 10);
        tree.insert(c2, w_size);

        REQUIRE(tree.search(2) != nullptr);

        terminal::Container c3(3, "c", 1, 1, 1, 10, 10);
        tree.insert(c3, w_size);

        REQUIRE(tree.search(3) != nullptr);

        terminal::Container c4(4, "c", 1, 1, 1, 10, 10);
        tree.insert(c4, w_size);

        REQUIRE(tree.search(4) != nullptr);

        terminal::Container c5(5, "c", 1, 1, 1, 10, 10);
        tree.insert(c5, w_size);

        REQUIRE(tree.search(5) != nullptr);

        terminal::Container c6(6, "c", 1, 1, 1, 10, 10);
        tree.insert(c6, w_size);

        REQUIRE(tree.search(6) != nullptr);

        terminal::Container c7(7, "c", 1, 1, 1, 10, 10);
        tree.insert(c7, w_size);

        REQUIRE(tree.search(7) != nullptr);

        terminal::Container c8(8, "c", 1, 1, 1, 10, 10);
        tree.insert(c8, w_size);

        REQUIRE(tree.search(8) != nullptr);

        tree.print(std::cout);

        SECTION("Removing") {

            tree.remove(8, 2);
            REQUIRE_THROWS_AS(tree.search(8), std::out_of_range);

            tree.remove(7, 2);
            REQUIRE_THROWS_AS(tree.search(7), std::out_of_range);

            tree.remove(6, 2);
            REQUIRE_THROWS_AS(tree.search(6), std::out_of_range);

            tree.remove(5, 2);
            REQUIRE_THROWS_AS(tree.search(5), std::out_of_range);

            tree.remove(4, 2);
            REQUIRE_THROWS_AS(tree.search(4), std::out_of_range);

            tree.remove(3, 2);
            REQUIRE_THROWS_AS(tree.search(3), std::out_of_range);

            tree.remove(2, 2);
            REQUIRE_THROWS_AS(tree.search(2), std::out_of_range);

            tree.remove(1, 2);
            REQUIRE_THROWS_AS(tree.search(1), std::out_of_range);

        }
    }

    SECTION("Insertion with coordinates") {
        terminal::Container c1(1, "a", 3, 3, 3, 10, 10);
        terminal::ContainerSpace cs1(0, 0, 0, 3, 3, 3, c1);
        tree.insert(cs1);

        REQUIRE(tree.search(1) != nullptr);

        terminal::Container c2(2, "b", 1, 1, 1, 10, 10);
        terminal::ContainerSpace cs2(3, 3, 3, 4, 4, 4, c2);
        tree.insert(cs2);

        REQUIRE(tree.search(2) != nullptr);

        terminal::Container c3(3, "c", 1, 1, 1, 10, 10);
        terminal::ContainerSpace cs3(5, 5, 5, 6, 6, 6, c3);
        tree.insert(cs3);

        REQUIRE(tree.search(3) != nullptr);

        terminal::ChilledContainer c4(4, "d", 1, 1, 1, 10, 10, 10);
        terminal::ContainerSpace cs4(5, 0, 0, 6, 1, 1, c4);
        tree.insert(cs4);

        REQUIRE(tree.search(4) != nullptr);

        SECTION("Replacing") {
            kdt::Point min1(3, 3, 3);
            REQUIRE_THROWS_AS(tree.replace(3, min1), std::runtime_error);

            kdt::Point min2(8, 8, 8);
            tree.replace(3, min2);
            std::vector<int> coords1 = {8, 8, 8, 9, 9, 9};
            std::vector<int> coords2 = tree.search(3)->space->getCoordinates();

            REQUIRE(coords1 == coords2);
        }
    }

}

