#include "glew.h"
#include "glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Macros
#define ASSERT(x) if (!(x)) __builtin_debugtrap();
#define GLCALL(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))


static void GLClearError(){
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line){
    while (GLenum error = glGetError()){
        std::cout << "[OpenGL Error]: " << error << " " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

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
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std:: endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void legacyOpenGL(void){
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f,-0.5f);
        glVertex2f( 0.0f, 0.5f);
        glVertex2f( 0.5f,-0.5f);
        glEnd();
}

void modernOpenGL(void){

    // Data
    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f};

    // Data buffer
    unsigned int buffer;
    glGenBuffers(1,&buffer);                                                            // Number of buffers, buffer ID
    glBindBuffer(GL_ARRAY_BUFFER,buffer);                                               // Select buffer
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);    // Load data

    // Attributes
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, sizeof(float)*2, 0);                   // Tell OpenGL how to interpret data

    // Index
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};
    
    // Index buffer
    unsigned int ibo;                                                                               // index buffer object
    glGenBuffers(1,&ibo);                                                                           // Number of buffers, buffer ID
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);                                                      // Select buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);       // Load data

    // Vertex Shader
    ShaderProgramSource source = ParseShader("shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Init GLEW (AFTER VALID CONTEXT!!! SEE DOCS)
    if(glewInit() != GLEW_OK){
        std::cout << "Error!" << std::endl;
    }

    // Print version
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Because data isn't changing every time, create data once.
    modernOpenGL();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        //legacyOpenGL();
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}