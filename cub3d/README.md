# 🧊 cub3d
A simple ray-casting engine

![Gameplay demo](./cub3d-vid.gif)

# About
Cub3D is a simple 3D game engine project based on raycasting, developed as part of the 42 Network. It is inspired by the classic game WOlfenstein 3D. The goal of this project is to render a 3D-like environment from a 2D map using C nad the MiniLibX (mlx) graphical library.

# Main objectives
- Render a 3D scene using raycasting
- Load and parse a map from ``.cub`` file
- Implement basic player movement (forward, backward, strafe, rotation)
- Handle textures for walls, floor and ceiling

# What we've added
- Basic collision detection
- Minimap
- Rotation that follow mouse movement

# Technologies
- C language
- MiniLibX
- Raycasting

# How to run (Linux)
Dowload project:
``git clone https://github.com/Zuraw7/cub3d.git``

Enter repository:
``cd cub3d``

Create an executable with Makefile:
``make``

Run:
``./cub3d ./maps/map00.cub``
