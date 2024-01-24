#include "./Game/Game.h"
#include <sol/sol.hpp>

void TestLua() {
    sol::state lua;

    lua.script_file("assets/scripts/myscript.lua");

    int someVariable = lua["some_variable"];

    std::cout << "This is the value" << std::to_string(someVariable) << std::endl;
}

int main(int argc, char* argv[]) {
    // Game game;

    // game.Initialize();
    // game.Run();
    // game.Destroy();

    TestLua();

    return 0;
}
