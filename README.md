# 2d-game-engine-course
2D Game Engine made from scratch from the Pikuma course made with C++, SDL2, glm and Lua.
Visit [pikuma.com](https://pikuma.com/courses/cpp-2d-game-engine-development) for move info on the course.

# Libraries and dependencies
In order for the project to run you need to install the following packages on your machine:

* **Make** -> for building and running the game
* **Lua** -> for the scripting system. Please note, you need to update the `LINKER_FLAGS` section with the specific version you are installing, e.g. 5.2. In addition if you are on Mac OS you need to remove the version from the flag, e.g. instead of `-llua5.3` you have to set it to `-llua`.
* **sdl2**, **sdl2_image**, **sdl2_ttf**, **sdl2_mixer** -> libraries to manage rendering of images, text and sound

Note: 

# Build the game
```
make build
```

# Run the game
```
make run
```

# Clean game executable file
```
make build
```