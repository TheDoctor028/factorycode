#pragma once
#include <unordered_map>
#include <string>
#include <vector>

#include "material.h"


namespace factorycode {
    enum Operation {
        None,
        Mine,
        Smelt,
    };

    struct Recipe {
        std::string name;

        MaterialStackList input;

        MaterialStackList output;

        // How many tick it takes to create the recipe.
        uint time;
    };

    static Recipe recipe(const std::string& name, const MaterialStackList& input, const MaterialStackList& output, const uint time = 0) {
        return {
            .name = name,
            .input = input,
            .output = output,
            .time = time
        };
    }

    const Recipe NoneVoid = recipe("void", {}, {}, 1) ;

    const inline std::vector<Recipe> recipes =  {
        recipe("ironMine", {}, {{IronOre, 1}}, 10),
        recipe("coalMine", {}, {{Coal, 1}}, 10),
        recipe("ironSmelt", {{Material::Coal, 1}, {Material::IronOre, 1}}, {{Material::Iron, 1}}, 10)
    };

    inline const std::unordered_map<Operation, std::unordered_map<Material, Recipe> > recipes_v2 = {
        {
            None,{
            { Void, NoneVoid }
            }
        },
        // Mind recipes
        {
            Mine, {
                {Coal, recipe("coalMine", {{Void, 0}}, {{Material::Coal, 1}}, 10)},
                {IronOre,  recipe("ironMine", {{Void, 0}}, {{IronOre, 1}}, 10),}
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

