```
                | (_) |       | |           | |           
 _ __ __ _ _   _| |_| |__  ___| |_ __ _ _ __| |_ ___ _ __ 
| '__/ _` | | | | | | '_ \/ __| __/ _` | '__| __/ _ \ '__|
| | | (_| | |_| | | | |_) \__ \ || (_| | |  | ||  __/ |   
|_|  \__,_|\__, |_|_|_.__/|___/\__\__,_|_|   \__\___|_|   
            __/ |                                         
           |___/  
```

# raylibstarter

[![CMakeBuilds](https://github.com/chfhhd/raylibstarter/actions/workflows/cmake.yml/badge.svg)](https://github.com/chfhhd/raylibstarter/actions/workflows/cmake.yml)

A simple raylib project template for CMake and C/C++

## Features

This project template contains several basic classes, e.g. for animated sprites, a simple scene manager and more.

It integrates the C++ wrapper raylib-cpp and includes and extensive API documentation.

## Usage

After downloading the repository, use CMake to build the project. The Raylib library and all other dependencies 
are downloaded automatically.

The project already contains three pre-built scenes - for the main menu, the actual game scene and a pause scene.

You can find more details about the usage in the docs: https://chfhhd.github.io/raylibstarter/

### Basic settings for the game

Basic settings, e.g. whether the game starts in fullscreen mode, sound and mouse support and much more can be 
configured in the file `src/config.h.in`.

### Changing the project title and version number

The project name and version number can be customized in the `src/CMakeLists.txt` file. By default, the project
name is 'game':

```
project(game VERSION 0.1 LANGUAGES CXX)
```

### Manage assets

Store assets in the designated `assets` folder. The project already contains some sample graphic files.

### Choose a different raylib version

Which raylib version is used can be specified in the `cmake/raylib.cmake` file. If this is changed after CMake has 
already created the project once, you must use CMake to completely rebuild the project.

### Build the API documentation

If you want to build the API documentation make sure you have Doxygen and Graphviz installed on your system. 
CMake will then create the API documentation automatically. It will be located in the build folder under
`src/docs_doxygen`.

### What next?

The template already contains a menu, game and pause scene. Add your code to the existing scenes under 
`src/scenes` and/or create new scenes. You may never need to change the `main.cpp` file or the `main()` 
function itself directly.

### Create a binary distribution

The cpack command can be used on the command line to create a binary distribution of the project, for example:

```
cpack -G ZIP -C Debug
```

All assets will be packed into the distribution.

## License

see `LICENCE` file for details.
