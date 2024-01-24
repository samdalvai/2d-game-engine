#include "./Game/Game.h"
#include <sol/sol.hpp>

void TestLua() {
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    lua.script_file("assets/scripts/myscript.lua");

    int someVariable = lua["some_variable"];

    std::cout << "This is the value in C++: " << std::to_string(someVariable) << std::endl;

    bool fullScreen = lua["config"]["fullScreen"];

    std::cout << "Fullscreen? " << fullScreen << std::endl;

    sol::table config = lua["config"];
    int width = config["resolution"]["width"];
    int height = config["resolution"]["height"];

    std::cout << "Height: " << std::to_string(width) << " Width: " << std::to_string(height) << std::endl;

    sol::function functionFactorial = lua["factorial_recursive"];
    int result = functionFactorial(5);
    std::cout << "Factorial in C++: " << std::to_string(result) << std::endl;
}

int main(int argc, char* argv[]) {
    // Game game;

    // game.Initialize();
    // game.Run();
    // game.Destroy();

    TestLua();

    return 0;
}
