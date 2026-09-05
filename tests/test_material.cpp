#include <catch2/catch_test_macros.hpp>
#include "game/material.h"

using namespace factorycode;

TEST_CASE("Material to_string conversion", "[material]") {
    REQUIRE(to_string(Material::Void) == "Void");
    REQUIRE(to_string(Material::Coal) == "Coal");
    REQUIRE(to_string(Material::IronOre) == "IronOre");
    REQUIRE(to_string(Material::Iron) == "Iron");
}

TEST_CASE("MaterialStackList basics", "[material_stack_list]") {
    SECTION("Empty list") {
        MaterialStackList list;
        REQUIRE(list.empty());
        REQUIRE(to_string(list) == "{}");
    }

    SECTION("Insert and has checks") {
        MaterialStackList list{{Material::Coal, 5}, {Material::IronOre, 10}};
        REQUIRE_FALSE(list.empty());
        REQUIRE(list.has(5, Material::Coal));
        REQUIRE(list.has(3, Material::Coal));
        REQUIRE_FALSE(list.has(6, Material::Coal));
        REQUIRE(list.has(10, Material::IronOre));
    }

    SECTION("Addition and subtraction") {
        MaterialStackList a{{Material::Coal, 5}};
        MaterialStackList b{{Material::Coal, 3}, {Material::Iron, 2}};

        a += b;
        REQUIRE(a.has(8, Material::Coal));
        REQUIRE(a.has(2, Material::Iron));

        a -= b;
        REQUIRE(a.has(5, Material::Coal));
    }
}
