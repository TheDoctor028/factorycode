#include <catch2/catch_test_macros.hpp>
#include <compare>
#include "game/Material.h"

using namespace factorycode;

SCENARIO("Comparing MaterialStackList with an integer threshold using spaceship operator", "[bdd][material][spaceship]") {
    GIVEN("A material stack with multiple resources") {
        MaterialStackList stack{{Material::Coal, 10}, {Material::IronOre, 8}};

        WHEN("Comparing against a threshold lower than all resource counts") {
            auto result = (stack <=> 5);

            THEN("The ordering result is strong_ordering::greater") {
                REQUIRE(result == std::strong_ordering::greater);
                REQUIRE((stack <=> 5) > 0);
            }
        }

        WHEN("Comparing against a threshold higher than at least one resource count") {
            auto result = (stack <=> 9);

            THEN("The ordering result is strong_ordering::less because IronOre count is below 9") {
                REQUIRE(result == std::strong_ordering::less);
                REQUIRE((stack <=> 9) < 0);
            }
        }

        WHEN("Comparing against a threshold higher than all resource counts") {
            auto result = (stack <=> 15);

            THEN("The ordering result is strong_ordering::less") {
                REQUIRE(result == std::strong_ordering::less);
                REQUIRE((stack <=> 15) < 0);
            }
        }
    }
}

SCENARIO("Comparing two MaterialStackList instances with spaceship operator", "[bdd][material][spaceship]") {
    GIVEN("An initial material stack list") {
        MaterialStackList base{{Material::Coal, 5}, {Material::IronOre, 10}};

        WHEN("Comparing with an identical material stack list") {
            MaterialStackList identical{{Material::Coal, 5}, {Material::IronOre, 10}};
            auto result = (base <=> identical);

            THEN("The comparison evaluates to strong_ordering::equal") {
                REQUIRE(result == std::strong_ordering::equal);
            }
        }

        WHEN("Comparing with a stack list having matching keys with greater quantities") {
            MaterialStackList higher{{Material::Coal, 10}, {Material::IronOre, 20}};
            auto result = (base <=> higher);

            THEN("The comparison evaluates to strong_ordering::greater") {
                REQUIRE(result == std::strong_ordering::greater);
            }
        }

        WHEN("Comparing with a stack list having lower quantities") {
            MaterialStackList lower{{Material::Coal, 2}, {Material::IronOre, 5}};
            auto result = (base <=> lower);

            THEN("The comparison evaluates to strong_ordering::less") {
                REQUIRE(result == std::strong_ordering::less);
            }
        }

        WHEN("Comparing with a stack list containing missing or mismatched keys") {
            MaterialStackList different{{Material::Iron, 5}};
            auto result = (base <=> different);

            THEN("The comparison evaluates to strong_ordering::less due to missing keys") {
                REQUIRE(result == std::strong_ordering::less);
            }
        }
    }
}

