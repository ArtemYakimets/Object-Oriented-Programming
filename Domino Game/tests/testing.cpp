#include <catch2/catch_all.hpp>
#include "../domino/domino_group.h"

TEST_CASE("DominoConstructor") {
    SECTION("DefaultConstructor") {
        lab2::Domino d(1, 1);
        REQUIRE(d.getEnd1());
        REQUIRE(d.getEnd2());
    }
}

TEST_CASE("DominoDisplayAsciiArt") {
    lab2::Domino domino(1, 2);

    SECTION("AsciiArtOutput") {
        std::stringstream output;
        // Сохраняем текущий вывод
        std::streambuf* coutBuffer = std::cout.rdbuf();
        // Перенаправляем вывод в std::stringstream
        std::cout.rdbuf(output.rdbuf());

        domino.displayAsciiArt();
        std::string outputStr = output.str();

        // Восстанавливаем стандартный вывод
        std::cout.rdbuf(coutBuffer);

        REQUIRE(outputStr.find("#######") != std::string::npos);
        REQUIRE(outputStr.find("#     #") != std::string::npos);
        REQUIRE(outputStr.find("#  1  #") != std::string::npos);
        REQUIRE(outputStr.find("#     #") != std::string::npos);
        REQUIRE(outputStr.find("#######") != std::string::npos);
        REQUIRE(outputStr.find("#     #") != std::string::npos);
        REQUIRE(outputStr.find("#  2  #") != std::string::npos);
        REQUIRE(outputStr.find("#     #") != std::string::npos);
        REQUIRE(outputStr.find("#######") != std::string::npos);
    }
}


TEST_CASE("DominoEqualityOperator") {
    lab2::Domino domino1(1, 2);
    lab2::Domino domino2(2, 1);
    lab2::Domino domino3(3, 3);

    SECTION("EqualDominos") {
        REQUIRE(domino1 == domino2);
    }

    SECTION("NonEqualDominos") {
        REQUIRE_FALSE(domino1 == domino3);
    }
}

TEST_CASE("DominoInversionOperator") {
    lab2::Domino domino(1, 2);
    lab2::Domino inverted = ~domino;

    SECTION("InvertedValues") {
        REQUIRE(inverted.getEnd1() == 2);
        REQUIRE(inverted.getEnd2() == 1);
    }
}

TEST_CASE("DominoOutputOperator") {
    lab2::Domino domino(1, 2);
    std::stringstream output;

    SECTION("OutputFormat") {
        output << domino;
        REQUIRE(output.str() == "1|2");
    }
}

TEST_CASE("DominoInputOperator") {
    lab2::Domino domino;
    std::stringstream input("3 4");

    SECTION("InputParsing") {
        input >> domino;
        REQUIRE(domino.getEnd1() == 3);
        REQUIRE(domino.getEnd2() == 4);
    }
}

TEST_CASE("DominoGroupConstruction") {
    SECTION("DefaultConstructor") {
        lab2::DominoGroup group;
        REQUIRE(group.getSize() == 0);
        REQUIRE(group.getCapacity() == 10);
    }

    SECTION("CapacityConstructor") {
        int capacity = 20;
        lab2::DominoGroup group(capacity);
        REQUIRE(group.getSize() == capacity);
        REQUIRE(group.getCapacity() == capacity);
    }

    SECTION("VectorConstructor") {
        std::vector<lab2::Domino> dominoes = {lab2::Domino(1, 2), lab2::Domino(3, 4)};
        lab2::DominoGroup group(dominoes);
        REQUIRE(group.getSize() == dominoes.size());
        REQUIRE(group.getCapacity() == dominoes.size());
    }
}

TEST_CASE("DominoGroupManipulation") {
    lab2::DominoGroup group;

    SECTION("AddDomino") {
        lab2::Domino domino(1, 2);
        group.addDomino(domino);
        REQUIRE(group.getSize() == 1);
        REQUIRE(group.getCapacity() == 10);
    }

    SECTION("RemoveDomino") {
        lab2::Domino domino(1, 2);
        group.addDomino(domino);
        lab2::Domino removedDomino = group.removeDomino(domino);
        REQUIRE(group.getSize() == 0);
        REQUIRE(removedDomino == domino);
    }

    SECTION("RemoveDominoByIndex") {
        lab2::Domino domino(1, 2);
        group.addDomino(domino);
        lab2::Domino removedDomino = group.removeDominoByIndex(0);
        REQUIRE(group.getSize() == 0);
        REQUIRE(removedDomino == domino);
    }

    SECTION("Clear") {
        lab2::Domino domino(1, 2);
        group.addDomino(domino);
        group.clear();
        REQUIRE(group.getSize() == 0);
        REQUIRE(group.getCapacity() == 10);
    }

    SECTION("SortBySumAscending") {
        lab2::Domino domino1(1, 2);
        lab2::Domino domino2(3, 4);
        group.addDomino(domino2);
        group.addDomino(domino1);
        group.sortBySumAscending();
        REQUIRE(group[0] == domino1);
        REQUIRE(group[1] == domino2);
    }

    SECTION("ExtractSubgroup") {
        lab2::Domino domino1(1, 2);
        lab2::Domino domino2(2, 3);
        lab2::Domino domino3(4, 5);
        group.addDomino(domino1);
        group.addDomino(domino2);
        group.addDomino(domino3);
        lab2::DominoGroup subgroup = group.extractSubgroup(2);
        REQUIRE(subgroup.getSize() == 2);
        REQUIRE(group.getSize() == 1);
    }

    SECTION("ExpandCapacity") {
        lab2::DominoGroup dg = lab2::DominoGroup::createRandomGroup(10);
        lab2::Domino d = lab2::Domino::createRandomDomino();
        dg.addDomino(d);
        REQUIRE(dg.getCapacity() == 20);
    }

    SECTION("CreateDominoGroupWithAllHints") {
        lab2::DominoGroup dg = lab2::DominoGroup::createGroupWithAllTypes(1);
        REQUIRE(dg.getSize() == 36);
    }

    SECTION("InputOperator") {
        std::stringstream ss("1\n1 2\n");
        ss >> group;
        REQUIRE(group.getSize() == 1);
        REQUIRE(group[0] == lab2::Domino(1, 2));
        //REQUIRE(group[1] == lab2::Domino(3, 4));
    }

    SECTION("OutputOperator") {
        lab2::Domino domino1(1, 2);
        lab2::Domino domino2(3, 4);
        group.addDomino(domino1);
        group.addDomino(domino2);
        std::stringstream ss;
        ss << group;
        std::string expectedOutput = "1|2 3|4 \n";
        REQUIRE(ss.str() == expectedOutput);
    }
}

TEST_CASE("DominoGroupAssignment") {
    lab2::DominoGroup group1;
    lab2::DominoGroup group2;

    SECTION("CopyAssignment") {
        lab2::Domino domino(1, 2);
        group1.addDomino(domino);
        group2 = group1;
        REQUIRE(group2.getSize() == group1.getSize());
        REQUIRE(group2.getCapacity() == group1.getCapacity());
    }

    SECTION("MoveAssignment") {
        lab2::Domino domino(1, 2);
        group1.addDomino(domino);
        group2 = std::move(group1);
        REQUIRE(group2.getSize() == 1);
        REQUIRE(group1.getSize() == 0);
    }
}


