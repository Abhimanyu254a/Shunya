# Shunya Game Engine

**Shunya** is a custom C++ game engine developed to explore the fundamentals of real-time rendering, engine architecture, and graphics programming.  
The engine is built using **OpenGL** and focuses on implementing core engine systems from scratch, including rendering, event handling, camera systems, and a 2D renderer.

This project was developed as part of my learning journey to understand how modern game engines work internally.

---

## Features

- Custom **OpenGL rendering pipeline**
- **Orthographic camera system**
- **2D renderer with textured quads**
- **Particle system**
- **ImGui editor integration**
- **Layer-based engine architecture**
- **Event system (keyboard, mouse, window events)**
- **Shader abstraction**
- **Texture loading**
- **Renderer command abstraction**

---

---

## Tech Stack

### Language
- C++

### Graphics
- OpenGL
- GLAD
- GLFW

### Math Library
- GLM

### UI
- ImGui

### Development Tools
- Visual Studio

---

## Renderer2D System

The 2D renderer allows drawing quads with color, textures, and transformations.

Supported features:

- Colored quads
- Textured quads
- Rotation
- Scaling
- Transformation matrices
- Batch-ready architecture

Example usage:

```cpp
Renderer2D::BeginScene(camera);

Renderer2D::DrawQuad(
    {0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f},
    texture
);

