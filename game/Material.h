#pragma once
#include <compare>
#include <initializer_list>
#include <unordered_map>
#include <utility>

namespace factorycode {
    enum Material {
        Void,
        Coal,
        IronOre,
        Iron,
    };

    typedef std::unordered_map<Material, int> material_map;

    /**
     * @brief Collection of materials and their quantities.
     */
    class MaterialStackList {
    protected:
        material_map collection;
    public:
        MaterialStackList() = default;
        explicit MaterialStackList(material_map m);
        MaterialStackList(const std::initializer_list<std::pair<const Material, int>> initLis);

        [[nodiscard]]
        material_map::const_iterator begin() const;

        [[nodiscard]]
        material_map::const_iterator end() const;

        void clear();

        std::pair<material_map::iterator, bool> insert(std::pair<Material, int> m);

        material_map::size_type erase(const Material m);

        material_map::iterator find(const Material m);

        [[nodiscard]] bool empty() const;

        void clear_zero_or_less();

        bool operator==(const MaterialStackList& outer) const;

        MaterialStackList& operator+=(const MaterialStackList& other);

        MaterialStackList& operator-=(const MaterialStackList& other);

        std::strong_ordering operator<=>(const int n);

        std::strong_ordering operator<=>(MaterialStackList& comp);
    };

}
