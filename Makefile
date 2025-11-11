############################################
# Makefile variables
############################################
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs"
INCLUDE_PATH_APPLE_SILICON = -I"/opt/homebrew/include" -I"./libs"
SRC_FILES = ./src/*.cpp ./src/**/*.cpp ./libs/imgui/*.cpp
# Mac OS linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua
LINKER_FLAGS_APPLE_SILICON = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua
# Other OS linker flags
#LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3
EXECUTABLE = gameengine

############################################
# Makefile rules
############################################
build:
	${CC} ${COMPILER_FLAGS} ${LANG_STD} ${INCLUDE_PATH} ${SRC_FILES} ${LINKER_FLAGS} -o ${EXECUTABLE};

build-apple-silicon:
	${CC} ${COMPILER_FLAGS} ${LANG_STD} ${INCLUDE_PATH_APPLE_SILICON} ${SRC_FILES} ${LINKER_FLAGS_APPLE_SILICON} -o ${EXECUTABLE};

run:
	./${EXECUTABLE}

clean:
	@rm -rf ${EXECUTABLE}