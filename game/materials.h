#pragma once
#include <ranges>
#include <unordered_map>
#include <utility>

namespace factorycode {
    enum Materials {
        Coal = 0,
        IronOre,
        Iron,
    };

    typedef std::unordered_map<Materials, int> material_map;

    class MaterialStackList {
    protected:
        material_map collection;
    public:
        MaterialStackList() = default;
        explicit MaterialStackList(material_map m): collection(std::move(m)) { }
        MaterialStackList(const std::initializer_list<std::pair<const Materials, int>> initLis): collection(initLis) {}


        [[nodiscard]]
        auto begin() const { return collection.begin(); }

        [[nodiscard]]
        auto end() const { return collection.end(); }

        void clear() { return collection.clear(); }

        auto insert(std::pair<Materials, int> m) { return collection.insert(m); }

        auto erase(const Materials m) { return collection.erase(m); }

        auto find(const Materials m) { return collection.find(m); }

        [[nodiscard]] bool empty() const { return collection.empty(); }

        void clear_zero_or_less() {
            for (const auto& pair : collection) {
                if (pair.second <= 0 ) this->collection.erase(pair.first);
            }
        }

        bool operator==(const MaterialStackList& outer) const {
            for (const auto& element : outer) {
                const auto e = collection.find(element.first);
                if (e == collection.end() || e->second != element.second) return false;
            }
            return true;
        }

        MaterialStackList& operator+=(const MaterialStackList& other) {
            for (auto value: other) {
                if (auto inner = collection.find(value.first); inner != collection.end()) {
                    inner->second += value.second;
                } else {
                    collection.insert(value);
                }
            }
            return *this;
        }

        MaterialStackList& operator-=(const MaterialStackList& other) {
            for (auto value: other) {
                if (auto inner = collection.find(value.first); inner != collection.end()) {
                    inner->second -= value.second;
                } else {
                    value.second *= -1;
                    collection.insert(value);
                }
            }
            return *this;
        }

        std::strong_ordering operator<=>(const int n) {
            for (const auto &val: collection | std::views::values) {
                if (val < n) return std::strong_ordering::less;
                if (val > n) return std::strong_ordering::greater;
            }
            return std::strong_ordering::equal;
        }

        std::strong_ordering operator<=>(MaterialStackList& comp) {
            for (const auto val: collection | std::views::values) {
                if (comp >= val) return std::strong_ordering::greater;
            }
            return std::strong_ordering::less;
        }
    };

    class Material {
    public:
        explicit Material(const Materials type): type(type) {

        }
        const Materials type;
    protected:

    };

};
