#include "Material.h"

#include <ranges>
#include <string>

namespace factorycode {

    MaterialStackList::MaterialStackList(material_map m) : collection(std::move(m)) {}

    MaterialStackList::MaterialStackList(const std::initializer_list<std::pair<const Material, int>> initLis)
        : collection(initLis) {}

    material_map::const_iterator MaterialStackList::begin() const {
        return collection.begin();
    }

    material_map::const_iterator MaterialStackList::end() const {
        return collection.end();
    }

    void MaterialStackList::clear() {
        collection.clear();
    }

    std::pair<material_map::iterator, bool> MaterialStackList::insert(std::pair<Material, int> m) {
        return collection.insert(m);
    }

    material_map::size_type MaterialStackList::erase(const Material m) {
        return collection.erase(m);
    }

    material_map::iterator MaterialStackList::find(const Material m) {
        return collection.find(m);
    }

    bool MaterialStackList::empty() const {
        return collection.empty();
    }

    void MaterialStackList::clear_zero_or_less() {
        for (const auto& pair : collection) {
            if (pair.second <= 0) this->collection.erase(pair.first);
        }
    }

    bool MaterialStackList::operator==(const MaterialStackList& outer) const {
        for (const auto& element : outer) {
            const auto e = collection.find(element.first);
            if (e == collection.end() || e->second != element.second) return false;
        }
        return true;
    }

    MaterialStackList& MaterialStackList::operator+=(const MaterialStackList& other) {
        for (auto value : other) {
            if (auto inner = collection.find(value.first); inner != collection.end()) {
                inner->second += value.second;
            } else {
                collection.insert(value);
            }
        }
        return *this;
    }

    MaterialStackList& MaterialStackList::operator-=(const MaterialStackList& other) {
        for (auto value : other) {
            if (auto inner = collection.find(value.first); inner != collection.end()) {
                inner->second -= value.second;
            } else {
                value.second *= -1;
                collection.insert(value);
            }
        }
        return *this;
    }

    std::strong_ordering MaterialStackList::operator<=>(const int n) {
        for (const auto& val : collection | std::views::values) {
            if (val < n) return std::strong_ordering::less;
            if (val > n) return std::strong_ordering::greater;
        }
        return std::strong_ordering::equal;
    }

    std::strong_ordering MaterialStackList::operator<=>(MaterialStackList& comp) {
        for (const auto val : collection | std::views::values) {
            if (comp >= val) return std::strong_ordering::greater;
        }
        return std::strong_ordering::less;
    }

    std::string to_string(Material m) {
        switch (m) {
            case Material::Void:    return "Void";
            case Material::Coal:    return "Coal";
            case Material::IronOre: return "IronOre";
            case Material::Iron:    return "Iron";
        }
        return "Unknown";
    }

    std::string to_string(const MaterialStackList& list) {
        if (list.empty()) return "{}";
        std::string result = "{ ";
        bool first = true;
        for (const auto& [mat, qty] : list) {
            if (!first) result += ", ";
            result += to_string(mat) + ": " + std::to_string(qty);
            first = false;
        }
        result += " }";
        return result;
    }

}
