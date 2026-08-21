#pragma once
#include <unordered_map>

#include "materials.h"


namespace factorycode {
    enum Operation {
        Mine,
        Smelt,
    };

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

    const inline std::vector<Recipe> recipes =  {
        recipe("ironMine", {}, {{IronOre, 1}}, 10),
        recipe("coalMine", {}, {{Coal, 1}}, 10),
        recipe("ironSmelt", {{Material::Coal, 1}, {Material::IronOre, 1}}, {{Material::Iron, 1}}, 10)
    };

    inline const std::unordered_map<Operation, std::unordered_map<Material, Recipe> > recipes_v2 = {
        // Mind recipes
        {
            Mine, {
                {Coal, recipe("coalMine", {}, {{Material::Coal, 1}}, 10)},
                {IronOre,  recipe("ironMine", {}, {{IronOre, 1}}, 10),}
            },
        },
        // Smelt recipes
        {
            Smelt,
            {
                {Iron, recipe("ironSmelt", {{Coal, 1}, {IronOre, 1}}, {{Iron, 1}}, 10)}
            }
        }
    };
}

