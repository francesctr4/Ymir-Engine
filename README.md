# Ymir Engine

### Repository Link: [Ymir Engine](https://github.com/francesctr4/Ymir-Engine)

### Current release version: None

### GitHub page: (In Progress)

## Description

Ymir Engine is part of the Game Engines subject, on the third year of the Videogame Design and Development degree, 
taught at CITM UPC (Terrassa) and supervised by [Miquel Suau](https://github.com/MayKoder).

The engine has been made from scratch in C++ using SDL and OpenGL to manage graphics.

<img src="https://github.com/francesctr4/Ymir-Engine/assets/99948892/4d6551ca-fa42-44fe-b81a-9cf5f62783ef" alt="YmirEngineLogo" width="400" height="400"/>

_Ymir Engine Logo_

## Team Members

_**Francesc Teruel Rodríguez**_
* **GitHub:** [francesctr4](https://github.com/francesctr4)

_**Joel Romero Botella**_
* **GitHub:** [Joeltecke25](https://github.com/Joeltecke25)

## Instructions

- How to use the engine, detailing the controls and any specific action
- Camera
- Editor Windows
- 

## Features

### v0.1 - Geometry Viewer

- Baker House automatically loaded at the start.
- Two models provided in FBX format with one channel diffuse texture.
- Drag&Drop of FBX files from anywhere in the Hard Drive.
- Drag&Drop of DDS/PNG files (apply the texture to the selected GameObject).
- GameObject structure, one for each loaded mesh.
- Three components available for the GameObjects: Transform, Mesh and Material.
- Unity-like camera controls.
- Editor Windows:
  - Console: the window should LOG the geometry loading process from ASSIMP and the external libraries initialization process.
○ Configuration:
- A graph for the frames per second.
- Configuration for all variables on each module (renderer, window, input, textures).

- Information output of memory consumption, hardware detection and software
versions (SDL, OpenGL, DevIL).

○ Hierarchy: you should display a list with all GameObjects in this window. The user should be
able to select a GameObject through this window.
- Inspector displays information about the components of the selected GameObject.

○ There must be a general menu with an option to quit, visit the github page and get info about
the engine (“About”). It should also be able to turn on/off editor windows.
○ There must be a menu to load your own basic shapes.

## Additional functionality (Cool features!!!)

- Early Shader Implementation for Rendering Geometry with VAO (Vertex Shader and Fragment Shader).
- Apply Transformations to Geometry with the Transform Component (Translation, Rotation and Scale).
- Custom Icon Uploaded to the Engine Executable.
