#include <iostream>
#include <string.h>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Window.hpp>

/*
 * This example exhibits the use of attribute definitions    for 
 * color in vertex shader for fragment shader; rather       than 
 * using a uniform or static color definition in fragment shader
 */
int main(void) {
    // Context and Window setup
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 2; // Optional
    sf::Window window(sf::VideoMode(1920, 1080), "OpenGL", sf::Style::Fullscreen, settings);

    // Match up graphics card GL support with GLEW before proceeding
    //  read: https://open.gl/context#Onemorething
    glewExperimental = GL_TRUE;
    glewInit();

    // Define a triangle's verticies and colour attributes
    /*

          1  *
          3 * * 2

    */
    float verticies[] = {
        // x, y, r, g, b
        0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // vertex 1
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // vertex 2
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // vertex 3
    };

    // Create Vertex Buffer Object (VBO)
    GLuint vbo;             // uint number for identifying buffer
    glGenBuffers(1, &vbo);  // generate buffer and assign ID

    // Activate array buffer for GL to manage
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Copy our vertex data to current active array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // Create our vertex shader using inline GLSL
    const char* vertexSource =
        "  #version 130\n                               "
        "  in vec2 position;                            "
        "  in vec3 color;                               "
        "  out vec3 Color;                              "
        "  void main() {                                "
        "    Color = color;                             "
        "    gl_Position = vec4(position, 0.0, 1.0);    "
        "  }                                            ";

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Checking if vertex shader compiled
    GLint vertexStatus;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexStatus);
    if (!(vertexStatus == GL_TRUE)) std::cout << "Failed to compile vertex shader" << std::endl;

    // Create our fragment shader using inline GLSL
    const char* fragmentSource =
        "  #version 130\n                   " 
        "  in vec3 Color;                   "
        "  out vec4 outColor;               "
        "  void main() {                    "
        "    outColor = vec4(Color, 1.0);   "
        "  }                                ";

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Checking if fragment shader compiled
    GLint fragmentStatus;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);
    if (!(fragmentStatus == GL_TRUE)) std::cout << "Failed to compile fragment shader" << std::endl;

    // Combine shaders into program so they can work together
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link shader program in with GL programmable processor
    //  read: http://docs.gl/gl3/glLinkProgram
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram); // start!

    // Create a Vertex Array Object (VAO) to track VBO attribute configs
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Define how our position data is formatted in our vector (the original verticies)
    //  note: 0, 0 is stride (bytes between each position attribute) and offset (bytes 
    //  from start of array where the attribute occurs)
    
    // Get reference to position input from vertex shader
    GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(positionAttribute);
    
    // Get reference to color input from vertex shader
    GLint colorAttribute = glGetAttribLocation(shaderProgram, "color");
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(colorAttribute);

    bool running = true;
    while (running)
    {
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            switch (windowEvent.type)
            {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::KeyPressed:
                    if (windowEvent.key.code == sf::Keyboard::Escape)
                        running = false;
                    break;
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle from 3 verticies
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.display();
    }
    
    // Clean up
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    window.close();

    return 0;
}

