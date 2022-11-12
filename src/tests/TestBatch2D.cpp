#include "TestBatch2D.hpp"

#include "Renderer.hpp"
#include "imgui-1.88/imgui.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace test {

    TestBatch2D::TestBatch2D()
        : m_translation(0.0f, 0.0f, 0.0f),                              // initial conditions x, y, z
        m_Proj(glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -1.0f, 1.0f)),      // x left, x right, y lower, y upper, z limits
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))     // ?
    {

    // Data
    float vertices[] = {
        -1.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, // x, y, z, r, g, b, alpha
        -0.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
        -1.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,

         0.5f, -0.5f, 0.0f, 1.0f, 0.9f, 0.2f, 1.0f,
         1.5f, -0.5f, 0.0f, 1.0f, 0.9f, 0.2f, 1.0f,
         1.5f,  0.5f, 0.0f, 1.0f, 0.9f, 0.2f, 1.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 0.9f, 0.2f, 1.0f
    };

    // Index
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,           // First square
        4, 5, 6, 6, 7, 4            // Second square
    };

    // Vertex Array
    m_VAO = std::make_unique<VertexArray>();

    // Vertex Buffer
    m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 4 * 7 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);      // x, y, z
    layout.Push<float>(4);      // r, g, b, a   TODO: Don't know why both objects don't appear...
    m_VAO->AddBuffer(*m_VertexBuffer, layout);

    // Index buffer
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12); 

    // Vertex Shader
    m_Shader = std::make_unique<Shader>("shaders/Batch2D.shader");
    m_Shader->Bind();
    
    }

    TestBatch2D::~TestBatch2D()
    {
    }

    void TestBatch2D::OnUpdate(float deltaTime){

    }

    void TestBatch2D::OnRender(){
        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestBatch2D::OnImguiRender(){
            ImGui::SliderFloat3("Translation", &m_translation.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}