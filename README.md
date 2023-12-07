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

<img src="https://github.com/francesctr4/Ymir-Engine/assets/99948892/d686ac0f-9cc2-43b1-b6dd-1682679b1617" alt="YmirEngineLogo" width="400" height="400"/>

_Ymir Engine Logo_

## Team Members

_**Francesc Teruel Rodríguez**_
* **GitHub:** [francesctr4](https://github.com/francesctr4)

_**Joel Romero Botella**_
* **GitHub:** [Joeltecke25](https://github.com/Joeltecke25)

## Disclaimer

- The Release build may weigh a little (1.300 KB) because of the .fbx stored in the Assets folder (Debug build weighs 4.800 KB).

## Instructions

### Controls

#### CAMERA

    - While Right Clicking, “WASD” FPS-like movement and free look around.
    - Mouse wheel zoom in and out.
    - "Alt" + Right Click (Press + Drag) orbits around the object.
    - Pressing “F” (or "Alt") focus the camera around the world (0,0,0).
    - Mouse Wheel Button + Drag pans around the viewport.
    - Holding SHIFT while moving the camera duplicates movement speed.

#### SCENE

    - "C" Clears the scene.
    - Hierarchy: Right click to select GameObject and Right click to delete selected GameObject.
    - Inspector: Drag Transform values to modify the mesh (only with shader enabled).
    - Drag and Drop: Drag .fbx or .png/.dds (to selected GameObject) directly to scene to load them.

#### EDITOR

    - File menu: Exit button to shut the engine.
    - GameObject menu: Create Empty and Primitives GameObjects and Clear Scene.
    - Windows menu: Application menu with general configurations of the engine and several editor 
    windows with utilities.
    - Help menu: About Modal Window with info of the engine and Repository link.

### Additional Instructions

- The shader is currently responsible for the transformations on the gameobjects, so if you upload a model without a texture,
the shader won't be enabled and the transformations won't be applied. To solve this apply the checker texture to the gameObject or
drag a texture to enable the shader.

- Moreover, the vertex normals and the face normals do not follow the GameObject transformations and they will be displayed as if
the geometry was in default state (because the normals aren't managed inside the shaders).

## Features

### v0.2 - Engine Editor

(Work In Progress)

### v0.1 - Geometry Viewer

![Geometry Viewer](https://github.com/francesctr4/Ymir-Engine/assets/99948892/4f386158-7507-4f23-83f4-87af180ec91e)

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

![Transformations GIF](https://github.com/francesctr4/Ymir-Engine/assets/99948892/8f27c2e9-ec37-41fc-b808-504c774a44e0)
![Primitive Library](https://github.com/francesctr4/Ymir-Engine/assets/99948892/830ed6e5-4216-4052-99ee-d4b58d29000e)

## Known bugs (Work in progress)

- There's some visual errors when deleting GameObjects from the hierarchy. The selected GameObject and his children are deleted, but the text of the parent is still displayed as if the GameObject
was still there (but it isn't). It is recommended to clear the scene pressing "C" to get rid of the corrupted GameObjects that may appear.

- There's some visual errors on the material component of the GameObjects in the inspector. When you upload a new model, the texture displayed from the older loaded meshes turns pitch black.

- There's also some visual errors on the transform component of the GameObjects in the inspector. When a model has several meshes and you select the model itself, there is n transform components
according to n meshes the model has and the Reset Transform button doesn't work properly in this situation. Regardless of the visual error, if you manipulate the first transform you will have the
same effect as having the parent transform matrix and the children will transform too.
