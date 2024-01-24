#include "./Game/Game.h"
#include <sol/sol.hpp>

void TestLua() {
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    lua.script_file("assets/scripts/myscript.lua");

    int someVariable = lua["some_variable"];

    std::cout << "This is the value in C++: " << std::to_string(someVariable) << std::endl;

    bool fullScreen = lua["config"]["fullScreen"];

    std::cout << "Fullscreen? " << std::to_string(fullScreen) << std::endl;
}

int main(int argc, char* argv[]) {
    // Game game;

    // game.Initialize();
    // game.Run();
    // game.Destroy();

    TestLua();

    return 0;
}
