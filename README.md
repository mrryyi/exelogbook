
exelogbook: exercise logbook application (WIP)
======

A desktop application with a GUI where you can enter exercise stuff and it will save in a local sqlite3 database.

In the future there will be a connecting backend that it will send to, which will also be a discord bot that does stuff too.

### Dependencies

* CMake
* vcpkg
* OpenGL
* Windows 10

### Building


I use CMake extensions in Visual Studio Code to build. You can do it manually or in visual studio if you are so inclined.

vcpkg should handle the dependencies brilliantly, do all that magic and put them in the build folder.
If you have trouble building because of changing directory name of where you're working, try deleting the generated build folder.

TODO: build scripts for release builds.

### Examples

TODO: The project has just been born