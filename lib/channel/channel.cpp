#include "channel.hpp"
#include <functional>

void go(const std::function<void()>& fnc) {
        auto t = std::thread([&] {
                fnc();
        });
        t.detach();
}

void go(const std::function<void()>& fnc, std::thread& thread) {
        thread = std::thread([&] {
                fnc();
        });
}
