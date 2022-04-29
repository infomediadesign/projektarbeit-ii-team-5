# FAQ

## Is it a complete game engine?

No - that is not the intention. It is a project template, which should facilitate the structured 
start of a new Raylib based C++ project. Some basic classes are already included, like a simple scene 
manager and a class for animated sprites.

## What do I have to do if I want to develop my own game?

The project template already comes with three simple scenes for the game menu, the actual game scene 
and a pause scene. The existing scenes can be easily extended.

Depending on the game type it may make sense to modify the basic classes or to develop further 
classes. E.g. for many games it becomes useful to develop a layer system, to realize a collision 
management, or similar.

## Is this project template based on raylib-cpp?

No - This project uses C++, but it is not based on raylib-cpp.

raylib-cpp is a third party C++ library for raylib. It provides object-oriented wrappers around 
raylib's structs and functions and make things more inline with C++'s language paradigm.

Even if this template does not use raylib-cpp itself it is integrated into the project template 
and can be used for your own development.

You can get more information about raylib-cpp here:

https://github.com/RobLoach/raylib-cpp