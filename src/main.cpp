#include "glew.h"
#include "glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath){
    std::ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream,line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else{
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}


static unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCALL(glShaderSource(id,1,&src,nullptr));
    GLCALL(glCompileShader(id));

    // Error handling
    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE){
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std:: endl;
        std::cout << message << std::endl;
        GLCALL(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return program;
}

void legacyOpenGL(void){
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f,-0.5f);
        glVertex2f( 0.0f, 0.5f);
        glVertex2f( 0.5f,-0.5f);
        glEnd();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Sync refresh rate
    glfwSwapInterval(1);

    // Init GLEW (AFTER VALID CONTEXT!!! SEE DOCS)
    if(glewInit() != GLEW_OK){
        std::cout << "Error!" << std::endl;
    }

    // Print version
    std::cout << glGetString(GL_VERSION) << std::endl;

        // Data
    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f};

    // Generate and bind Vertex Array Object
    unsigned int vao;
    GLCALL(glGenVertexArrays(1,&vao));
    GLCALL(glBindVertexArray(vao));

    // Data buffer
    VertexBuffer vb(positions, 4*2*sizeof(float));


    // Attributes
    GLCALL(glEnableVertexAttribArray(0)); 
    GLCALL(glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, sizeof(float)*2, 0));                   // Tell OpenGL how to interpret data

    // Index
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    // Index buffer
    IndexBuffer ib(indices, 6);

    // Vertex Shader
    ShaderProgramSource source = ParseShader("shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCALL(glUseProgram(shader));

    // Send color info to shader
    GLCALL(int location = glGetUniformLocation(shader,"u_Color"));
    ASSERT(location != -1);

    // zero everything for so we're demoing calls in the loop.
    GLCALL(glBindVertexArray(0));
    GLCALL(glUseProgram(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER,0));                        // Select buffer
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));                   // Select buffer

    // Color changing variables
    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        //legacyOpenGL();
        GLCALL(glUseProgram(shader));
        GLCALL(glUniform4f(location, r, 0.3f, 0.5f, 1.0f));

        GLCALL(glBindVertexArray(vao));
        ib.Bind();
        
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f ){
            increment = -0.05f;
        } else if (r < 0.0f){
            increment = 0.05f;
        }
        r+=increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}