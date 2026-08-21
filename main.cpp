#include <fstream>
#include <iostream>
#include <sstream>
#include <wasmtime.hh>
#include <filesystem>
#include <random>

#include "game/Game.h"
#include "game/recipe.h"


using namespace wasmtime;

std::string readFile(const char *name) {
    std::ifstream watFile;
    watFile.open(name);
    std::stringstream strStream;
    strStream << watFile.rdbuf();
    return strStream.str();
}

static Module compile_cpp_wasm(Engine &engine, const std::string &file) {

    const auto tmpDir = std::filesystem::temp_directory_path();
    const auto random = std::rand() % 1000000000000000000;

    const std::string output = tmpDir.string() + std::to_string(random)  + ".wasm";

    const std::string command = "zig c++ -target wasm32-freestanding -O3 " + file + " -o " + output + " -Wl,--no-entry";
    if (const int status = std::system(command.c_str()); status != 0) {
        std::cerr << "Failed to compile cpp to wasm." << "\n\n";
        exit(status);
    }

    auto contet = readFile(output.c_str());

    auto module = Module::compile(engine, Span(reinterpret_cast<uint8_t*>(contet.data()), contet.size())).unwrap();

    return module;
}

void webassTest() {
    // First the wasm module needs to be compiled. This is done with a global
    // "compilation environment" within an `Engine`. Note that engines can be
    // further configured through `Config` if desired instead of using the
    // default like this is here.
    std::cout << "Compiling module\n";
    Engine engine;

    const auto module = compile_cpp_wasm(engine, "examples/hello.cpp");

    // After a module is compiled we create a `Store` which will contain
    // instantiated modules and other items like host functions. A Store
    // contains an arbitrary piece of host information, and we use `MyState`
    // here.
    std::cout << "Initializing...\n";
    Store store(engine);

    // Our wasm module we'll be instantiating requires one imported function.
    // the function takes no parameters and returns no results. We create a host
    // implementation of that function here.
    std::cout << "Creating callback...\n";
    Func host_func =
        Func::wrap(store, []() { std::cout << "Calling back...\n"; });

    // Once we've got that all set up we can then move to the instantiation
    // phase, pairing together a compiled module as well as a set of imports.
    // Note that this is where the wasm `start` function, if any, would run.
    std::cout << "Instantiating module...\n";
    auto instance = Instance::create(store, module, {host_func}).unwrap();

    // Next we poke around a bit to extract the `run` function from the module.
    std::cout << "Extracting export...\n";
    auto run = std::get<Func>(*instance.get(store, "run"));

    // And last but not least we can call it!
    std::cout << "Calling export...\n";
    run.call(store, {}).unwrap();

    std::cout << "Done\n";
}

int main() {
    using namespace factorycode;
    auto game = Game();

    auto coalMine = Machine(recipes_v2.at(Operation::Mine).at(Material::Coal));
    auto ironMine = Machine(recipes_v2.at(Operation::Mine).at(Material::IronOre));

    auto conveyor = Conveyor();

    auto smelter = Machine(recipes_v2.at(Operation::Smelt).at(Material::Iron));

    game.place(coalMine, {0, 0});
    game.place(ironMine, {1, 0});

    game.place(conveyor, {0, 1});

    game.place(smelter, {1, 1});

    game.connectMachines(coalMine, conveyor);
    game.connectMachines(ironMine, smelter);
    game.connectMachines(conveyor, smelter);

    game.tick();
    game.tick();
    game.tick();
    game.tick();
    return 0;
}
