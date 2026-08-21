#pragma once
#include "materials.h"
namespace factorycode {
    struct Recipe {
        std::string name;

        MaterialStackList& input;

        MaterialStackList& output;

        // How many tick it takes to create the recipe.
        uint time;
    };

    static Recipe recipe(const std::string& name, MaterialStackList input, MaterialStackList output, const uint time = 0) {
        return {
            .name = name,
            .input = input,
            .output = output,
            .time = time
        };
    }

    inline std::vector<Recipe> recipes =  {
        recipe("ironMine", {}, {{IronOre, 1}}, 10),
        recipe("coalMine", {}, {{Coal, 1}}, 10),
        recipe("ironSmelt", {{Materials::Coal, 1}, {Materials::IronOre, 1}}, {{Materials::Iron, 1}}, 10)
    };
}

