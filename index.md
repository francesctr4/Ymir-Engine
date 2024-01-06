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

- Team or members photo and quick explanation of the individual work of each member.

### _**Francesc Teruel Rodríguez**_

![profile](https://github.com/francesctr4/Ymir-Engine/assets/99948892/9d5a7869-07fb-407c-b0e6-7201c8fa4307)

Game Developer in C++ and C# with high focus on low level systems and engine-related programming.

* ### Contributions to the project:
  * filler text
  
* **GitHub:** [francesctr4](https://github.com/francesctr4)

### _**Joel Romero Botella**_

* **GitHub:** [Joeltecke25](https://github.com/Joeltecke25)
  
# Ymir Engine: Main Core Sub-Systems

The engine is made from several core sub-systems that work together to provide the necessary features 
to the user, in order to serve as an environment to create games:

## Geometry Viewer

### Editor



### Graphics Pipeline (with Shaders)



### Drag & Drop



### GameObject Structure & Components


### Hierarchy & Inspector


### Console



## Engine Editor

### Camera Frustum


### Time Management


### Serialization


### Custom File Format


### Scene & Game Framebuffers


### Resource Management



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

### v0.2 - Engine Editor

- GameObjects can be picked from the world using the mouse.
- All meshes use a bounding volume (AABB) and can be discarded using Frustum Culling.
- Models, meshes and textures are saved to Ymir Engine format under “Library” folder.
- Scene is serialized to a file that can be loaded.
- The user can Start / Pause / Stop the simulation and recover its original state.
- The editor has 2 windows:
    - One with the scene (Editor view).
    - Another one captured from a GameObject with a camera component (Main Game Camera).
    - Each one has its own framebuffer and the user can visualize both at the same time.
- Resource Management:
    - Assets Window that shows all user assets.
    - The user can drop/import new files. Assets window reacts properly.
    - On first use, the temporal folder Library is created and meta files are generated for each new imported asset.
    - Library can be regenerated if deleted.
    - The imported assets are saved in Library folder with Ymir Engine custom file format.

## Additional functionality (Cool features!)

- There is a space skybox by default. In the folder Assets/Skybox there is more skybox textures in case you want to test several environments.
- The Assets and Library Windows have some files highlighted on blue, you can interact with them to read the contents inside the engine.
- When you select a GameObject, the shader makes an orange highlight to the mesh.
- There is an option in Inspector -> Mesh Component to turn on/off the Normal Map of the selected Mesh (done by shader).
- The Gizmo has been implemented and can be used to manage GameObjects' transformations.
- The shaders now can be loaded using a single file instead of separating Vertex Shader and Fragment Shader.
- Added Node Editor for future material editing with shaders.

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
