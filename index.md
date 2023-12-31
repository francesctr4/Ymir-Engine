# Introduction

## What is a Split Screen and what is it used for?

The Split Screen is an audiovisual output display where the screen has been divided into two or more exactly equal areas so that players can explore different areas simultaneously without having to be close to each other.

Here's an example of F1 2021 Split Screen for two players:

![F1 2021 Split Screen](https://user-images.githubusercontent.com/99948892/227244798-628ae660-a067-4f6b-a617-acba9d766183.png)

## Why is it important to have a Split Screen?

The Split Screen feature is commonly used in non-networked multiplayer video games, also known as couch co-op, and allows multiple people to play on a single device.

Here's an exmple of Mario Kart 8 Deluxe Split Screen for four players:

![Mario Kart 8 Deluxe Split Screen](https://user-images.githubusercontent.com/99948892/227245049-b9618d18-b295-43f7-b1ca-21391522dc6a.png)

## Context and History

The Split Screen gaming is said to have originated in the mid 1980's, when early home consoles like the Atari 2600 and the Intellivision featured games that could be played by two players on the same screen:

![Bloodwych (1989)](https://user-images.githubusercontent.com/99948892/227245225-0f74d12b-ffd7-45aa-adda-d0d8676cea9e.png)

_Bloodwych (1989)_

![Lotus Esprit Turbo Challenge (1990)](https://user-images.githubusercontent.com/99948892/227245318-3fb740f9-239b-4dd3-b1f2-267bf2cefc4e.png)

_Lotus Esprit Turbo Challenge (1990)_

When Lemming was released for Commodore's Amiga (1991), it was the first Amiga game to support two simultaneous players with a Split Screen on the 
same computer while players used separate mice. However Split Screen gaming wasn't popularized until GoldenEye 007 in 1997, allowing players to take 
place in a four person deathmatch on the same screen:

![Lemming (1991)](https://user-images.githubusercontent.com/99948892/227245386-1c0a6f85-b01e-4a7d-a9ea-833c2da5c8a5.png)

_Lemming (1991)_

![GoldenEye 007 (1997)](https://user-images.githubusercontent.com/99948892/227248629-d8a75ddc-bd98-4193-9868-865b7cc243fe.png)

_GoldenEye 007 (1997)_

Continued in 2001 with Halo: Combat Evolved on the XBOX, leading other shooters to pick up the trend, such as Gears of War and Call of Duty:

![Halo: Combat Evolved (2001)](https://user-images.githubusercontent.com/99948892/227245606-a8a063fd-e0d4-4050-893c-8ce6439d1694.png)

_Halo: Combat Evolved (2001)_

![Call of Duty 2 (2005)](https://user-images.githubusercontent.com/99948892/227245700-d1f9916a-974d-4759-a3e3-857187098987.png)

_Call of Duty 2 (2005)_

## Current references

Currently in the industry, we can observe recent games that use Split Screen. Here are some videos that show current examples:

### Rocket League (2015)

<iframe width="560" height="315" src="https://www.youtube.com/embed/sf4RgCDbM58" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

### It Takes Two (2021)

<iframe width="560" height="315" src="https://www.youtube.com/embed/GAWHzGNcTEw" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

# Current State

## Technical evolution of the Split Screen

The Split Screen technique has historically been very popular on consoles, which until the 2000s did not have access to the internet or any other network.
However, it is less commmon today with modern support for console-to-console online multiplayer. 

The Split Screen is useful for those who want to play with other players, but with only one console. In recent years, this has not been used very often because 
the new frontier of video games is to play with other players online, without sharing a screen.

## Current techniques in the industry

### Standard Split Screen

By standard split screen we mean the common split screen, where the regions are divided equally for all players.

Here you can see an example of the Sonic & All-Stars Racing Transformed Collection Split Screen:

![Sonic & All-Stars Racing Transformed Collection (2013)](https://user-images.githubusercontent.com/99948892/227247720-c0a9fdf5-3a23-4633-a19b-081b906459b3.png)

### Voronoi Split Screen

The Voronoi Split Screen is a variant of the Standard Split Screen. This effect divides the screen into multiple regions based on the proximity between the players or to different objects or points of interest in the game world. It is often used in coop multiplayer games to provide a more immersive and engaging gaming experience, as well as a more stylish version of the casual Split Screen.

You can see an example of this type of Split Screen in the .gif below:

![Voronoi Split Screen](https://jorgegh2.github.io/Split-screen/Voronoi_2_Players.gif)

And here you can see an example of a game that uses this technique, Lego Batman 3: Beyond Gotham Split Screen:

![Lego Batman 3: Beyond Gotham (2014)](https://user-images.githubusercontent.com/99948892/227248245-05c2b3ad-2b68-452a-909c-90fa023fe42a.png)

## Split Screen in other game engines

In this section we can find several videos on how to add a Split Screen to our games in other game engines, such as Unity, Unreal and Godot:

### Unity

<iframe width="560" height="315" src="https://www.youtube.com/embed/rw2VKAdTdgQ" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

### Unreal

<iframe width="560" height="315" src="https://www.youtube.com/embed/ipU4MtV-O_8" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

### Godot

<iframe width="560" height="315" src="https://www.youtube.com/embed/1XdjHIshYY4" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

If you spend some time watching the videos, you will realise that it is relatively easy to make a Split Screen in the current game engines on the market. However, in SDL this is a bit more complicated.

# Selected Approach

## Basic concepts

### Window 
The Window is a separate viewing area on a computer display screen as part of a GUI.

### Render
To Render is the process that turns the code you write on an application into something visible and/or interactive on screen.

### Renderer
The Renderer is the piece of code that turns code instructions into an interactive rendering context.

### Camera
The Camera designates the point of view that the players will have presented on their screens. 

### Viewport
The Viewport is a region of the screen used to display a portion of the total image to be shown.

## ¿Renderer vs Camera vs Viewport?

The difference between renderer, camera and viewport is that the renderer is the part of the code that renders the developer's input to the screen, 
while the camera is a rectangular region delimited by the developer that serves as a magnifying glass to observe the rendered content, 
and the viewport is the region of the window where the camera can be moved and objects can be rendered.

## How could we theoretically code a Split Screen?

Theoretically, to code a Split Screen, it would be enough to multiply the number of elements on screen by the number of cameras needed, 
and then rearrange the cameras to show them equally on screen.

![Split Screen Utopia](https://user-images.githubusercontent.com/99948892/227253435-7ecc7063-1216-4c2a-a99c-e8b1f146c209.png)

But in SDL2, it is not so easy...

## In SDL2 we have to look for another way

### We can’t create multiple renderers.
### We can’t create multiple cameras.
### We can’t create multiple viewports.

At least, we can't create multiple elements directly, by simply declaring them. We have to take into account that SDL only supports 1 renderer, 
and multiple cameras and viewports can be supported, but only if we code them with classes and several reusable functions.

## Then, how can we program a Split Screen in SDL2?

### New features

In order to create my implementation of the Split Screen, I have added the following features to the code:

* New Camera Class

![New_Features_1](https://user-images.githubusercontent.com/99948892/227253880-807bd675-0d38-4f83-a1dc-0bdb439be0e3.png)

* New Players

![New_Features_2](https://user-images.githubusercontent.com/99948892/227253955-2dee202b-3ad8-4628-95a9-cda8aafe1fba.png)

* New Map

![New_Features_3](https://user-images.githubusercontent.com/99948892/227254057-c30509ca-cd9e-4297-bf7b-fd65292e1035.png)

### Affected modules

* Camera → The camera attribute is now a class.
* Player → Multiple players with different input.
* Scene → The scene will split in n screens.
* Render → Manage multiple viewports and cameras.

### New functions

* Render.cpp

![New_Functions_1](https://user-images.githubusercontent.com/99948892/227254223-6f272fb3-7529-4599-af19-3820a0e95573.png)

* Scene.cpp

![New_Functions_2](https://user-images.githubusercontent.com/99948892/227254275-3f325fdf-0f57-4ea2-93e2-3330123552ee.png)

* Player.cpp

![New_Functions_3](https://user-images.githubusercontent.com/99948892/227254329-cc233418-41ea-420a-aed0-27a829312cb3.png)

### Steps to follow

The overall steps to code a Split Screen in SDL2 are shown below:

1. Create the cameras and add them to a list.
2. Relate the different players with the cameras.
3. Assign and center the cameras to the players.
4. Finally, display the desired cameras.

Here you can find the location of the TODOs inside the code:

![All_TODOs](https://user-images.githubusercontent.com/99948892/227254474-9a30f69a-456d-47d0-9bf0-5fcdf9ab2bc9.png)

# Split Screen Handout & Solution

All the material provided (handout, solution and presentation) can be downloaded by clicking this link:

### [Download Provided Material](https://github.com/francesctr4/SplitScreen/archive/refs/heads/main.zip)

### TODO 1 → [Render.cpp]
### “Create cameras according to a viewport”

* First create a Camera* with the viewport defined
* Then add the camera to the cameras list
* Don’t forget to clear the cameras list

![TODO 1](https://user-images.githubusercontent.com/99948892/227061306-41568d6d-1769-4885-9462-44ebd0c9ced8.png)

### TODO 2 → [Player.cpp]
### “Manage players movement and camera”

* Read the parameters from config.xml
* Then use the function HandleInput to manage the camera-player-input relation

![TODO 2.1](https://user-images.githubusercontent.com/99948892/227061545-10c1719e-4356-4efd-ac43-142c79e7657d.png)

![TODO 2.2](https://user-images.githubusercontent.com/99948892/227061574-8d4a79ae-7d23-44aa-8753-0183929767e6.png)

### TODO 3 → [Scene.cpp]
### “Instantiate the players in the scene”

* Read the config.xml and retrieve all the player nodes
* Then you have to CreateEntity of each player
* Don’t forget to add them to the players list

![TODO 3](https://user-images.githubusercontent.com/99948892/227061519-a9e45b39-7443-492d-8a9e-3645a7def82a.png)

### TODO 4 → [Render.cpp]
### “Get the viewport of each active camera”

* You need a loop to go through the list of cameras
* For each camera, state renderer and viewport
* You can retrieve the viewport of the cameras

![TODO 4](https://user-images.githubusercontent.com/99948892/227061466-5e230e87-7bd7-47ca-9a98-58328ba1c05a.png)

### TODO 5 → [Render.cpp]
### “Center each active camera to a player”

* Very similar loop to TODO 4
* But now the loop has two iterators
* You have to increment it after each iteration

![TODO 5](https://user-images.githubusercontent.com/99948892/227061423-3f448e8e-b911-4898-a4bc-5dc2899e688c.png)

### TODO 6 → [Scene.cpp]
### “Create all the necessary cameras”

* Check the function CreateCameras
* Check the enum class DisplayType

![TODO 6](https://user-images.githubusercontent.com/99948892/227061370-2e8c3613-9fbb-4680-ba4d-2297d2eadcc7.png)

## Results

### One Screen
![ONE_SCREEN](https://user-images.githubusercontent.com/99948892/227045336-ce753db3-f400-4d8f-849f-9633457ac9d4.png)

### Two Screens (Vertical)
![TWO_VERTICAL](https://user-images.githubusercontent.com/99948892/227045341-c1b03904-5ede-4d00-8ed5-b368c2c323d9.png)

### Two Screens (Horizontal)
![TWO_HORIZONTAL](https://user-images.githubusercontent.com/99948892/227045344-c21b2ccc-bf39-43e9-91e9-bf008cbc3204.png)

### Three Screens (Align Left)
![THREE_LEFT](https://user-images.githubusercontent.com/99948892/227045349-7625d11b-ce6a-4449-a9d0-61827eacf2c1.png)

### Three Screens (Align Center)
![THREE_CENTERED](https://user-images.githubusercontent.com/99948892/227045351-607e58de-3fc8-4a8a-b482-18539ba95bce.png)

### Three Screens (Align Right)
![THREE_RIGHT](https://user-images.githubusercontent.com/99948892/227045352-6396a525-127a-4e4e-9e16-8c1dc14d84b8.png)

### Four Screens
![FOUR_SCREENS](https://user-images.githubusercontent.com/99948892/227045355-35c6e569-ca34-409d-8882-1036e3aeef22.png)

# Possible Improvements

## Problems of this implementation in SDL2

* The number of screens and their position are hardcoded, so to increase the number of screens shown in the window, it would have to be done manually.
* Four players appear regardless of the number of cameras. This is because the cameras are created first and then the players are instantiated, but by doing it with XML you do not know in advance how many cameras there will be.
* There's a little visual bug on the edges of the cameras if you pay attention to it.

## Features you could add to your Split Screen

* Ability to change screen display mode mid-game.
* Render line, circle and text taking into account viewport margins.
* An algorithm that makes n screens for n players.
* ...

# Conclusions

## Advantages of the Split Screen

* Players can see where the other players are.
* Only one console needed.
* Only one copy of the game needed.
* There's no need for internet access.
* There's no internet connection problems.

## Disadvantages of the Split Screen

* Screens are smaller and make visibility more difficult.
* Rendering more screens causes several performance issues.
* More distraction, especially from game sounds.
* Lower active resolution for each player.

# References

This section gathers all the references used during the development of the research:

## Articles

* [Visión general de F1 2021](https://www.ea.com/es-es/games/f1/f1-2021/game-overview)
* [Wikipedia - Pantalla dividida](https://es.wikipedia.org/wiki/Pantalla_dividida) 
* [Ultimate Pop Culture Wiki - Split screen (video games)](https://ultimatepopculture.fandom.com/wiki/Split_screen_(video_games))
* [Split-Screen: Videogame History through Local Multiplayer Design](https://philarchive.org/archive/KARSV)
* [Game Developer - Shared-Multi-Split Screen Design](https://www.gamedeveloper.com/design/shared-multi-split-screen-design) 
* [Voronoi split screen: A Quick Tour](https://mattwoelk.github.io/voronoi_split_screen_notes/)

## Videos

* [Rocket League - Splitscreen Multiplayer Gameplay Trailer](https://youtu.be/sf4RgCDbM58) 
* [It Takes Two – Official Gameplay Trailer](https://youtu.be/GAWHzGNcTEw)
* [How To Create A Split Screen In Unity](https://youtu.be/rw2VKAdTdgQ) 
* [UE4 Split Screen](https://youtu.be/ipU4MtV-O_8) 
* [UE4 - Tutorial - Local Splitscreen!](https://youtu.be/68ViQFeE02o) 
* [How to Easily Add Split Screen Multiplayer in Godot](https://youtu.be/1XdjHIshYY4)
* [Voronoi Split Screen System](https://youtu.be/vsRrB0ZggE4)

## Previous years approach

* [Split Screen (2021)](https://lucaspg14.github.io/Split-Screen/) by [Lucas Pérez](https://github.com/LucasPG14)
* [Split Screen (2019)](https://jorgegh2.github.io/Split-screen/) by [Jorge Gemas](https://github.com/jorgegh2)

