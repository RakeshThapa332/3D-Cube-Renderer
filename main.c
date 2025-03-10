#include <GL/glew.h>               // Include GLEW to manage OpenGL extensions
#include <GLFW/glfw3.h>            // Include GLFW for window management and input handling
#include <GL/gl.h>                 // Include OpenGL header
#include <GL/glu.h>                // Include OpenGL Utility Library header
#include <stdio.h>                 // Include standard input/output header

// Vertices for a cube centered at the origin
float vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,          // Bottom-left corner
     0.5f, -0.5f,  0.5f,          // Bottom-right corner
     0.5f,  0.5f,  0.5f,          // Top-right corner
    -0.5f,  0.5f,  0.5f,          // Top-left corner
    
    // Back face
    -0.5f, -0.5f, -0.5f,          // Bottom-left corner
     0.5f, -0.5f, -0.5f,          // Bottom-right corner
     0.5f,  0.5f, -0.5f,          // Top-right corner
    -0.5f,  0.5f, -0.5f           // Top-left corner
};

// Correct indices for cube faces
unsigned int indices[] = {
    0, 1, 2, 2, 3, 0,             // Front face
    5, 4, 7, 7, 6, 5,             // Back face
    4, 0, 3, 3, 7, 4,             // Left face
    1, 5, 6, 6, 2, 1,             // Right face
    3, 2, 6, 6, 7, 3,             // Top face
    4, 5, 1, 1, 0, 4              // Bottom face
};

// Colors for each face
float colors[] = {
    1.0f, 0.0f, 0.0f,             // Red (front)
    0.0f, 1.0f, 0.0f,             // Green (back)
    0.0f, 0.0f, 1.0f,             // Blue (left)
    1.0f, 1.0f, 0.0f,             // Yellow (right)
    1.0f, 0.0f, 1.0f,             // Magenta (top)
    0.0f, 1.0f, 1.0f              // Cyan (bottom)
};

float rotationX = 0.0f;           // Initial rotation around X-axis
float rotationY = 0.0f;           // Initial rotation around Y-axis
float translateX = 0.0f;          // Initial translation along X-axis
float translateY = 0.0f;          // Initial translation along Y-axis
float scaleX = 1.0f;              // Initial scaling factor along X-axis
float scaleY = 1.0f;              // Initial scaling factor along Y-axis
float shearX = 0.0f;              // Initial shearing factor along X-axis
float shearY = 0.0f;              // Initial shearing factor along Y-axis
int firstMouse = 1;               // Flag to check if this is the first mouse event

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);      // Enable depth testing
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set clear color to dark gray
}

void setupProjection(int width, int height) {
    glMatrixMode(GL_PROJECTION);  // Switch to projection matrix mode
    glLoadIdentity();             // Reset projection matrix
    gluPerspective(45.0f, (double)width / height, 0.1f, 100.0f);  // Set perspective projection
    glMatrixMode(GL_MODELVIEW);   // Switch back to modelview matrix mode
}

void renderCube() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear color and depth buffers
    glLoadIdentity();                                   // Reset modelview matrix
    
    // Apply transformations
    // Translation
    glTranslatef(translateX, translateY, -5.0f);        // Translate the cube

    // Rotation based on cursor position
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);             // Rotate around X-axis
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);             // Rotate around Y-axis
    
    // Scaling
    glScalef(scaleX, scaleY, 1.0f);                     // Scale the cube
    
    // Shearing (using a shear matrix)
    GLfloat shearMatrix[16] = {
        1.0f, shearX, 0.0f, 0.0f,                       // Shear matrix for X-axis
        shearY, 1.0f, 0.0f, 0.0f,                       // Shear matrix for Y-axis
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glMultMatrixf(shearMatrix);                         // Apply shear transformation
    
    // Draw the cube with colored faces
    glBegin(GL_TRIANGLES);                              // Begin drawing triangles
    for (int face = 0; face < 6; face++) {
        // Set color for this face
        glColor3f(colors[face*3], colors[face*3+1], colors[face*3+2]);
        
        // Draw the two triangles that make up this face
        for (int tri = 0; tri < 6; tri++) {
            int idx = face * 6 + tri;                   // Get index for this triangle
            int vertexIdx = indices[idx];               // Get vertex index
            glVertex3f(vertices[vertexIdx * 3], 
                      vertices[vertexIdx * 3 + 1], 
                      vertices[vertexIdx * 3 + 2]);    // Specify vertex coordinates
        }
    }
    glEnd();                                            // End drawing triangles
    
    glFlush();                                          // Ensure all commands are executed
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    static double lastX = 400, lastY = 300; // Initial values set to the center of the window

    if (firstMouse) {
        lastX = xpos;                       // Set lastX to current position
        lastY = ypos;                       // Set lastY to current position
        firstMouse = 0;                     // Clear firstMouse flag
    }

    rotationY += (xpos - lastX) * 0.1f;     // Update rotation around Y-axis based on mouse movement
    rotationX += (ypos - lastY) * 0.1f;     // Update rotation around X-axis based on mouse movement
    lastX = xpos;                           // Update lastX to current position
    lastY = ypos;                           // Update lastY to current position
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Ensure that we only react to key press events
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_UP:
                translateY += 0.1f;         // Translate up
                break;
            case GLFW_KEY_DOWN:
                translateY -= 0.1f;         // Translate down
                break;
            case GLFW_KEY_LEFT:
                translateX -= 0.1f;         // Translate left
                break;
            case GLFW_KEY_RIGHT:
                translateX += 0.1f;         // Translate right
                break;
            case GLFW_KEY_W:
                rotationX -= 5.0f;          // Rotate around X-axis upwards
                break;
            case GLFW_KEY_S:
                rotationX += 5.0f;          // Rotate around X-axis downwards
                break;
            case GLFW_KEY_A:
                rotationY -= 5.0f;          // Rotate around Y-axis left
                break;
            case GLFW_KEY_D:
                rotationY += 5.0f;          // Rotate around Y-axis right
                break;
            case GLFW_KEY_Q:
                scaleX -= 0.1f;             // Scale down along X-axis
                scaleY -= 0.1f;             // Scale down along Y-axis
                break;
            case GLFW_KEY_E:
                scaleX += 0.1f;             // Scale up along X-axis
                scaleY += 0.1f;             // Scale up along Y-axis
                break;
            case GLFW_KEY_Z:
                shearX += 0.1f;             // Shear along X-axis
                break;
            case GLFW_KEY_X:
                shearX -= 0.1f;             // Shear along X-axis
                break;
            case GLFW_KEY_C:
                shearY += 0.1f;             // Shear along Y-axis
                break;
            case GLFW_KEY_V:
                shearY -= 0.1f;             // Shear along Y-axis
                break;
            case GLFW_KEY_R:
                // Reset transformations
                rotationX = 0.0f;           // Reset rotation around X-axis
                rotationY = 0.0f;           // Reset rotation around Y-axis
                translateX = 0.0f;          // Reset translation along X-axis
                translateY = 0.0f;          // Reset translation along Y-axis
                scaleX = 1.0f;              // Reset scaling factor along X-axis
                scaleY = 1.0f;              // Reset scaling factor along Y-axis
                shearX = 0.0f;              // Reset shearing factor along X-axis
                shearY = 0.0f;              // Reset shearing factor along Y-axis
                break;
        }
    }
}

void showDisclaimer() {
    printf("Controls:\n");                 // Print control instructions
    printf("Arrow keys: Translate the cube\n");
    printf("W/S: Rotate the cube around the X-axis\n");
    printf("A/D: Rotate the cube around the Y-axis\n");
    printf("Q/E: Scale the cube\n");
    printf("Z/X: Shear the cube along the X-axis\n");
    printf("C/V: Shear the cube along the Y-axis\n");
    printf("R: Reset transformations to original state\n");
}

int main() {
    if (!glfwInit()) {                     // Initialize the GLFW library
        fprintf(stderr, "Failed to initialize GLFW\n");  // Print error if initialization fails
        return -1;                         // Exit with error code
    }
    
    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(800, 600, "3D Cube", NULL, NULL);
    if (!window) {                         // Check if window creation failed
        fprintf(stderr, "Failed to create GLFW window\n");  // Print error if creation fails
        glfwTerminate();                   // Terminate GLFW
        return -1;                         // Exit with error code
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);        // Set the window context as current
    glfwSwapInterval(1);                   // Enable vsync
    
    // Initialize GLEW to access modern OpenGL functions
    GLenum err = glewInit();               // Initialize GLEW
    if (err != GLEW_OK) {                  // Check if initialization failed
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));  // Print error message
        return -1;                         // Exit with error code
    }
    
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));  // Print OpenGL version
    
    initOpenGL();                          // Initialize OpenGL settings
    
    // Set cursor position callback
    glfwSetCursorPosCallback(window, cursorPositionCallback);  // Set callback for cursor position
    
    // Set key callback
    glfwSetKeyCallback(window, keyCallback);  // Set callback for key events
    
    // Show disclaimer with controls
    showDisclaimer();                      // Show control instructions
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {  // Loop until the window should close
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);  // Get current framebuffer size
        glViewport(0, 0, width, height);    // Set viewport to cover the new window
        setupProjection(width, height);     // Set up projection matrix
        
        renderCube();                       // Render the cube
        
        glfwSwapBuffers(window);            // Swap front and back buffers
        glfwPollEvents();                   // Poll for and process events
    }
    
    glfwDestroyWindow(window);              // Destroy the window
    glfwTerminate();                        // Terminate GLFW
    return 0;                               // Exit with success code
}