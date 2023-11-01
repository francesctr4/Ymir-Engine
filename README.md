# Ymir Engine

### Repository Link: [Ymir Engine](https://github.com/francesctr4/Ymir-Engine)

### Current release version: v0.1

### GitHub page: (In Progress)

## Description

Ymir Engine is part of the Game Engines subject, on the third year of the Videogame Design and Development degree, 
taught at CITM UPC (Terrassa) and supervised by [Miquel Suau](https://github.com/MayKoder).

The engine has been made from scratch in C++ using SDL and OpenGL to manage graphics. The main target of the project is to
be able to integrate complex systems such as graphics management and game engine architecture in a simple and understandable way
for educational purposes.

<img src="https://github.com/francesctr4/Ymir-Engine/assets/99948892/4d6551ca-fa42-44fe-b81a-9cf5f62783ef" alt="YmirEngineLogo" width="400" height="400"/>

_Ymir Engine Logo_

## Team Members

_**Francesc Teruel Rodríguez**_
* **GitHub:** [francesctr4](https://github.com/francesctr4)

_**Joel Romero Botella**_
* **GitHub:** [Joeltecke25](https://github.com/Joeltecke25)

## Disclaimer

- The Release build may weigh a little (1.300 KB) because of the .fbx stored in the Assets folder (Debug build weighs 4.800 KB).

## Instructions

- How to use the engine, detailing the controls and any specific action
- Camera
- Editor Windows
- ...etc
- The shader is currently responsible for the transformations on the gameobjects, so if you upload a model without a texture,
the shader won't be enabled and the transformations won't be applied. To solve this apply the checker texture to the gameObject or
drag a texture to enable the shader.

## Features

### v0.1 - Geometry Viewer

![Geometry Viewer](https://github.com/francesctr4/Ymir-Engine/assets/99948892/c8c38732-7e81-4c16-bd9e-e5d04c50272b)

- Baker House automatically loaded at the start.
- Two models provided in FBX format with one channel diffuse texture.
- Drag&Drop of FBX files from anywhere in the Hard Drive.
- Drag&Drop of DDS/PNG files (apply the texture to the selected GameObject).
- GameObject structure, one for each loaded mesh.
- Three components available for the GameObjects: Transform, Mesh and Material.
- Unity-like camera controls.
- Editor Windows:
  - Console: Show LOGs.
  - Configuration:
    - A graph for the frames per second.
    - Configuration for variables on each module (renderer, window, input, textures).
    - Information output of memory consumption and hardware detection.
    - OpenGL configuration.
    - ...and more!
  - Hierarchy: list with all GameObjects with tree structure. The user is able to select a GameObject through this window.
  - Inspector: displays information about the components of the selected GameObject.
- About Modal Window to get info about the engine.
- Menu to load basic shapes.

## Additional functionality (Cool features!)

- Early Shader Implementation for Rendering Geometry with VAO (Vertex Shader and Fragment Shader).
- Apply Transformations to Geometry with the Transform Component (Translation, Rotation and Scale).
- Custom Icon Uploaded to the Engine Executable.
- Extensive primitive library inside the engine on GameObject menu.

![Transformations GIF](https://github.com/francesctr4/Ymir-Engine/assets/99948892/f3373cbd-b132-4d8a-b73e-017c2ca833f5)
![Primitive Library](https://github.com/francesctr4/Ymir-Engine/assets/99948892/09808392-234b-4ed6-82f2-c7fe84f4aa7c)

## Known bugs (Work in progress)

- There's some visual errors on the material component of the GameObjects in the inspector. When you upload a new model, the texture displayed from the older loaded meshes turns pitch black.
- There's also some visual errors on the transform component of the GameObjects in the inspector. When a model has several meshes and you select the model itself, there is n transform components
according to n meshes the model has and the Reset Transform button doesn't work properly in this situation. Regardless of the visual error, if you manipulate the first transform you will have the
same effect as having the parent transform matrix and the children will transform too.
