# MiniECS
Naive ECS implementation

## Description
This project's goal is to implement a simple ECS framework for data oriented game objects management.

This repository consists of a solution with 2 projects: Engine and Game. This is to demonstrate how the Engine itself can be built as a standalone library and the Game is just a framework application.

## Build
Premake5 is used to create the solution files and build setup. For simplest build process you can download Premake5 binary or compile one yourself.

### Windows - Visual Studio 2017
- copy **premake5.exe** to repository root and run **premake5.bat**
- open **MiniEngine.sln** and build the **Game** project

Executables will be placed in **(solution root)/_exe/(build configuration)/**
