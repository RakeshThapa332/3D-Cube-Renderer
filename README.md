# 🖥️ 3D Cube Renderer in C 🎮  

## 📌 Overview  
This project is a **3D Cube Renderer** developed in **C using OpenGL, GLFW, and GLEW**. It allows users to interact with a cube by applying real-time **transformations** such as **translation, rotation, scaling, and shearing**. The project demonstrates fundamental **computer graphics concepts** and serves as a foundation for more advanced applications in **3D modeling, simulations, and game development**.  

## ✨ Features  
✅ **3D rendering** using OpenGL  
✅ **Keyboard & Mouse controls** for real-time manipulation  
✅ **Perspective projection** for depth perception  
✅ **Transformations**: Translation, Rotation, Scaling, Shearing  
✅ **Depth buffering** for correct visibility  
✅ **Cross-platform support** with GLFW  

## 🛠️ Technologies Used  
| Technology | Purpose |  
|------------|---------|  
| **C Language** | Core programming |  
| **OpenGL** | 3D rendering API |  
| **GLEW** | Manages OpenGL extensions |  
| **GLFW** | Handles window creation & user input |  
| **GLU** | Provides perspective projection utilities |  

## 📥 Installation  
To set up and run the project, follow these steps:  

### **🔹 Prerequisites**  
Ensure you have the following installed on your system:  
- **OpenGL** (Graphics API)  
- **GLFW** (Window & input handling)  
- **GLEW** (Extension manager)  
- **C Compiler (GCC, MinGW, or MSVC)**  

### **🔹 Clone the Repository**  
```sh
git clone https://github.com/RakeshThapa332/3D-Cube-Renderer.git
cd 3D-Cube-Renderer
```
🔹 Compile and Run

For Windows:

```sh
gcc main.c -o cube.exe -lglfw3 -lopengl32 -lglew32 -lgdi32
cube.exe
```
For Linux:
```sh
gcc main.c -o cube -lglfw -lGL -lGLEW -lm -lGLU
./cube
```
🎮 Controls


⬆️ ⬇️ ⬅️ ➡️ =	Translate the cube

W/S =	Rotate along X-axis

A/D =	Rotate along Y-axis

Q/E	 = Scale the cube

Z/X	= Shear along X-axis

C/V =	Shear along Y-axis

R	 =Reset transformations

🖱️ Mouse =	Rotate dynamically

🖼️ Screenshots


![Screenshot (41)](https://github.com/user-attachments/assets/742c5c6b-f59b-4348-a25c-71d27368e19e)
![Screenshot (39)](https://github.com/user-attachments/assets/ed0cc7de-ee46-48e5-b132-5c645535f92b)

🔧 Future Improvements

🚀 Implement lighting & shading for realism

🚀 Add texture mapping for detailed surfaces

🚀 Introduce camera controls for free movement

🚀 Expand to multiple 3D objects

🚀 Improve performance with modern OpenGL (VAOs & VBOs)



📝 License
This project is licensed under the [MIT License](LICENSE).
