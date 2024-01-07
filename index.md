# Ymir Engine: Project Description

Ymir Engine is part of the Game Engines subject, on the third year of the Videogame Design and Development degree, 
taught at CITM UPC (Terrassa) and supervised by [Miquel Suau](https://github.com/MayKoder).

The engine has been made from scratch in C++ using SDL and OpenGL to manage graphics. The main target of the project is to
be able to integrate complex systems such as graphics management and game engine architecture in a simple and understandable way
for educational purposes.

<p align="center">
  <img src="https://github.com/francesctr4/Ymir-Engine/assets/99948892/d686ac0f-9cc2-43b1-b6dd-1682679b1617" alt="YmirEngineLogo" width="400" height="400"/>
</p>

# Team Members: About Us

### _**Francesc Teruel Rodríguez**_

![Francesc](https://github.com/francesctr4/Ymir-Engine/assets/99948892/9d5a7869-07fb-407c-b0e6-7201c8fa4307)

Game Developer in C++ and C# with high focus on low level systems and engine-related programming.
  
* **GitHub:** [francesctr4](https://github.com/francesctr4)

### _**Joel Romero Botella**_

<img src="https://github.com/francesctr4/Ymir-Engine/assets/99948892/c35d1fd0-f955-4701-b52c-fce1050910da" alt="Joel" width="400"/>

Game Designer specialized in the field of characters and levels, with a medium level of knowledge in 3D Modeling.

* **GitHub:** [Joeltecke25](https://github.com/Joeltecke25)
  
# Ymir Engine: Main Core Sub-Systems

The engine is made from several core sub-systems that work together to provide the necessary features 
to the user, in order to serve as an environment to create games:

## Geometry Viewer

### Editor

* The engine uses Dear ImGui to provide several windows to customize and manage different aspects of the engine,
in order to serve as a controller for the user to take advantage of the features implemented on the engine.

![Editor](https://github.com/francesctr4/Ymir-Engine/assets/99948892/86ab7a4b-2204-49c4-8e50-d3df6fc46cec)

### Graphics Pipeline (with Shaders)

* The engine uses Assimp to import the desired geometry into the engine. The rendering pipeline involves loading the meshes from Assimp
and creating the necessary OpenGL buffers to generate the geometry.

* Moreover, in the case of this engine, shaders are being used alongside the buffers and a Vertex Array Object (VAO) in order to use
the programmable pipeline of OpenGL and to be able to do the Shader Pipeline as the last assignment's High-Level System.

### Drag & Drop

* 3D Models with the format .fbx and textures with the format .png or .dds can be dragged directly onto the scene
from the file explorer and the engine will load the elements.

### GameObject Structure & Components

* The engine has a GameObject tree structure, where the scene itself is the root of that tree and the several elements
on the scene are children of the root node. Each mesh and element is its own gameobject, with components that can be modified.

* The GameObjects can have children and parents, the same way as Unity manages its gameobjects.
  
* Available Components:
  * Component Transform: manages the GameObject transformation (translation, rotation, scale).
  * Component Mesh: manages the GameObject mesh and geometry.
  * Component Material: manages the GameObject appearance (shader and textures).
  * Component Camera: creates a camera on the GameObject and serves as a POV (point of view) for the Game Camera.

### Hierarchy & Inspector

* Hierarchy: a window that displays the full GameObject tree structure of the current scene.
* Inspector: a window that displays information about the active components of the current selected GameObject on the scene.

![Hierarchy](https://github.com/francesctr4/Ymir-Engine/assets/99948892/20a4fb0c-ab60-41c5-ad65-0d50524fd4be)

![Inspector](https://github.com/francesctr4/Ymir-Engine/assets/99948892/d049d089-3f79-4528-80e5-f1690cb8c3b3)

### Console

* An ImGui window that displays all the engine messages and LOGs so that the user can see and understand what's going on.

![Console](https://github.com/francesctr4/Ymir-Engine/assets/99948892/93786131-1b3a-4291-b242-c8f9536fc1b7)

## Engine Editor

### Camera Frustum

* The camera of the engine has been reworked into a MathGeoLib frustum, that manages all the calculations of the matrices internally.
It is really useful to be able to implement the Frustum Culling system, that discards GameObjects outside the Game Camera.

![Frustum](https://github.com/francesctr4/Ymir-Engine/assets/99948892/dc064540-e025-48c2-b725-f0a848e36865)

### Scene & Game Framebuffers

* The engine has two ImGui windows to separate the game view from scene view, just as Unity does. In order to achieve this functionality,
two OpenGL framebuffers have been created, one in each camera, in the respective ImGui window so that we are able to see the two points
of view simultaneously.

![Framebuffers](https://github.com/francesctr4/Ymir-Engine/assets/99948892/47d58086-2554-4f6c-b533-69bcc49d4566)

### Custom File Format

* Ymir Engine has its own custom file format for some of the files that can be opened with it:

  * Meshes --> .ymesh
  * Models --> .ymodel
  * Scenes --> .yscene
  * Materials --> .ymat (not implemented yet)
 
* They are saved in Library folder using the custom file format.

![CFF1](https://github.com/francesctr4/Ymir-Engine/assets/99948892/ab4936cb-8735-4006-a326-2bae3e5d8f1e)

![CFF2](https://github.com/francesctr4/Ymir-Engine/assets/99948892/66f07bbb-c153-4b91-9563-05836f5633c0)

### Serialization

* Serialization is the process of converting data structures or objects into a format that can be easily stored, transmitted, or reconstructed later.
The engine does this in order to save the GameObject stucture of the Scene (including the Components), so that it can be saved and reconstructed when loaded.

* The GameObjects in the scene are identified using an UID (Unique IDentificator). Some other elements in the engine also use the UID format to be identified,
for example, the textures.

### Resource Management

* A resource manager is a subsystem responsible for managing and controlling the usage of various resources required by the application.
Resources in this context typically include assets such as textures, meshes, models, and other data needed for rendering graphics and
supporting other game features.

* In the case of Ymir Engine, the Resource Manager it's the Achilles Heel of the core subsystems, because it's not completely finished and
the resources are still not managed properly. If the project ends up growing in the future, the next step for sure will be fixing the resource manager.

![Resource1](https://github.com/francesctr4/Ymir-Engine/assets/99948892/79c5c036-07d0-4c7e-87f5-fcd899c95c7b)

![Resource2](https://github.com/francesctr4/Ymir-Engine/assets/99948892/2ddb6453-0925-4e57-85c7-a8a2143a298c)

![Resource3](https://github.com/francesctr4/Ymir-Engine/assets/99948892/a7082f29-5866-4ced-9547-331468235fb8)

### Time Management

* The engine has a Play/Stop/Step system that manages the simulation of the game scene. At the moment the functionality is limited
because of the resource manager current state, but all the timers and buttons work correctly.

![Time1](https://github.com/francesctr4/Ymir-Engine/assets/99948892/1caf83d5-7453-4b6f-bd8f-48c5443d7f5b)
![Time2](https://github.com/francesctr4/Ymir-Engine/assets/99948892/47ca44dd-7ed7-4d1e-b6a7-cfaf982e28e3)
![Time3](https://github.com/francesctr4/Ymir-Engine/assets/99948892/7e8caf8e-43df-4f95-a773-567b8bd4e7ca)

# High-Level System: Shader Pipeline

The last assignment sub-system chosen for Ymir Engine was the Shader Pipeline, which is the sequence of stages that a graphics processing unit (GPU) 
goes through to render graphics in computer graphics applications. Shaders are small programs written in languages like OpenGL Shading Language (GLSL) 
that run on the GPU and are used to control various aspects of the rendering process.

* In order to implement the Shader Pipeline in the engine, several features have been developed. They are explained below:

### Shader Pipeline for rendering geometry (VAO)

The rendering pipeline of the engine uses shaders alongside a Vertex Array Object (VAO) in order to draw geometry into screen.
Here are some screenshots from the code itself that show the insides of the mesh drawing of the engine:

* Bind Buffers

![VAO](https://github.com/francesctr4/Ymir-Engine/assets/99948892/7a2e6c77-168c-4b87-9150-11f95a977b5c)

* Draw Geometry while binding the current Shader

![Rendering](https://github.com/francesctr4/Ymir-Engine/assets/99948892/070cdaca-06e9-4e1b-a30b-6ddccb8c8061)

### Shader Editor

The Shader Editor is an ImGui Window with a Text Editor that is capable of reading GLSL language attached to it.
It has an input text field that displays the name of the current shader (modifiable) and several buttons:

* **Create Shader**: writes the default shader as base on the shader editor to help you start creating your shader.

* **Save Shader**: saves the shader file in "Assets/Shaders/ directory, compiles and loads the shader into the engine.
After saving the shader, you can select it from the list of loaded shaders on the Component Material of the GameObjects.
In case you were opening an existing shader, it will update the new contents and recompile the shader on the engine.

* **Delete Shader**: deletes the current shader opened at the shader editor, from the memory, the list of loaded shaders,
the files and lastly from the shader editor itself. No trace of that shader on the engine anymore.

If you want to open an existing shader on your project, you can do it by going to the Assets Window and then opening
the Shaders/ folder, and then click on the shader to open it on the Shader Editor.

![Shader Editor](https://github.com/francesctr4/Ymir-Engine/assets/99948892/dfa4dc53-4d90-413c-bd67-f83e198f6cb5)

### Shader Hot Reload

* Saving a Shader or changing to another Shader inside the Component Material of a GameObject will recompile the 
shader on runtime, so that you can see the changes at the moment.

![Hot Reload](https://github.com/francesctr4/Ymir-Engine/assets/99948892/5bc1645a-6de5-4bc7-b604-b90ee96f364c)

### Compilation Messages and Errors

When the process of compilation of a shader is executed, the engine will display some messages on the console,
depending on the result of the compilation.

* The first case shows a correct compilation of a Vertex Shader and a Fragment Shader:
  
![Correct](https://github.com/francesctr4/Ymir-Engine/assets/99948892/fb0065ae-f0cd-4a1c-973e-334107494724)

* The second case shows an error of compilation in a shader that was trying to be loaded to memory:

![Error](https://github.com/francesctr4/Ymir-Engine/assets/99948892/c8b53d7e-b66d-44d6-9cdc-a90f4939678a)

### Dynamic Uniform Detection

When you load a Shader on the engine, it has an algorythm to detect editable uniforms that you may have created on the
shader's code. Once detected, the engine displays them for you on the inspector and binds them with the shader code, so
that you can modify the value from the inspector directly without having to hardcode them.

* The engine is capable of distinguish between int, float, bool and vectors, and shows you the appropiate ImGui widget to modify
the value accordingly.

* Some Uniforms may appear on the shader code but not in the inspector. That's because they are essential for the shader functionality
and shouldn't be manipulated by the user. Some examples of this kind of uniforms are: model, view, projection, selected and time.

* If you delete an existing editable uniform from a shader and then recompile it, the inspector will react as well and will delete that
uniform from the list because is no longer there. The same happens if you add a new uniform on the code and save the changes (it will
be added to the list of uniforms and will appear on the inspector).

![Dynamic Uniform Detection](https://github.com/francesctr4/Ymir-Engine/assets/99948892/035d0867-9977-46af-bc0f-2d74130cdbf6)

### Shader Library

The engine keeps track of the loaded shaders and lets you change between them on the Component Material of the GameObjects.

* If some shader is loaded or deleted, the engine will react accordingly and will modify the list of loaded shaders.

![Shader Library](https://github.com/francesctr4/Ymir-Engine/assets/99948892/7ceac485-7f61-4a56-afae-99c31081b3c4)

### Water Shader

There is a flat mesh (plane) on the scene that simulates simple water. The shader is made from:

* Vertex Shader: creates simple wave movement using sinusoidal functions.
* Fragment Shader: the color of the pixels changes based on its height (dark blue on the bottom, light blue/white on the top).

![Water Shader](https://github.com/francesctr4/Ymir-Engine/assets/99948892/4611846f-ed47-4209-864a-2e98939c84e5)

### ...and more shaders!

* In order to test the capabily of the engine to actually create the shaders and use them on runtime, some shaders have 
been created:

#### Lava Shader

* Water Shader Variant

![Lava Shader](https://github.com/francesctr4/Ymir-Engine/assets/99948892/dfecc094-7a8f-45c9-89e7-301fc4ab66b9)

#### Rainbow Shader 

* Mario Bros Star Effect

![Rainbow Shader](https://github.com/francesctr4/Ymir-Engine/assets/99948892/27e77ceb-043a-4add-a81f-ede8fd426cd5)

#### Color Shader

* Add color to the material of a GameObject. You can even modify some light settings!

![Color Shader](https://github.com/francesctr4/Ymir-Engine/assets/99948892/e1b75436-febf-4141-a79b-c329a9a35b6e)

# Workflow Video

* Finally, this video shows a speed-up showcase on how to create the demo scene, required for the final delivery of the Game Engines subject, from scratch.
Moreover, the video emphasizes the Shader Pipeline and shows the general functionality of all the systems explained above.

<iframe width="560" height="315" src="https://www.youtube.com/embed/KRQcgcFDksc?si=ImCD4ViJ6wsMqt0H" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

# Repository and Releases

### Repository Link: [Ymir Engine](https://github.com/francesctr4/Ymir-Engine)

### Last Release Link: (not yet)

# License

MIT License

Copyright (c) 2023 Francesc Teruel Rodríguez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.