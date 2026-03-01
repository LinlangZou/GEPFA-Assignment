
<img width="775" height="459" alt="Witch Survivor Banner" src="https://github.com/user-attachments/assets/aecc2f91-7aad-42b5-87db-e4dfd3c11e22" />



# 🔮 Witch Survivor

**A magic-themed rogue-lite horde survival game.**


---

## 📖 About the Project

> The night falls, and the monsters surge like a tide. As the last witch, can you survive the endless darkness until dawn?

**Witch Survivor** is a C++ 2D action game in a Vampire Survivors–style roguelike, with player movement and combat, NPC AI and projectiles, tile-based world, camera follow, and save/load, built on a custom graphics framework.This project leverages the GamesEngineeringBase C++ framework to demonstrate core game development principles and technologies.




<br>

### ✨ Core Features

* 🎥 **Custom 2D Virtual Camera System:** Implements robust world-to-screen coordinate transformations to ensure seamless entity tracking and fluid rendering.
* 👾 **Dynamic Spawning & Difficulty Scaling:** Features four distinct enemy archetypes (Melee, Tank, Ranged, and Elite). Utilizes optimized off-screen spawning algorithms coupled with adaptive difficulty progression.
* 💥 **High-Precision Collision Detection:** Employs a hybrid collision architecture, combining circular bounding boxes with multi-point tile collision queries for accurate spatial interactions.
* 🎯 **Advanced Targeting & Ballistics:** Implements linear projectile trajectories targeting the nearest entity, visually augmented by **Bresenham's Line Algorithm**. Features intelligent AOE mechanics that dynamically sort and target enemies based on HP thresholds.
* ⚡ **Dynamic Progression System:** Kill-triggered enhancement loop that programmatically modifies player DPS via real-time fire rate buffs and increased AOE target caps.
* 🗺️ **Optimized Rendering Pipeline:** Built on a data-driven tilemap architecture utilizing strict **Viewport Culling**, significantly reducing draw calls and rendering overhead for out-of-bounds sprites.
* 💾 **Lightweight Data Persistence:** Features a custom **Binary Serialization** system for rapid, low-overhead game state saving and loading (Hotkeyed to `K`/`L`).
* 📊 **Built-in Telemetry:** Integrated real-time FPS monitoring and basic performance profiling tools to track rendering and logic bottlenecks on the fly.

## 🎥 Demo Video


https://github.com/user-attachments/assets/1b68f0d7-8c6c-44d8-8c6d-c900d9faa469

## 🚀 Build & Run

1. Clone the repository to your local machine.
2. Open the solution file (`.sln`) in **Visual Studio 2022**.
3. Ensure the active solution platform is set to **x64**.
4. Make sure you have the necessary Windows SDK installed (Windows 10 or 11 SDK) with DirectX 12 support.
5. Build the solution (`Ctrl + Shift + B`).
6. Run the project (`F5` or `Ctrl + F5`) to launch the playable level.
