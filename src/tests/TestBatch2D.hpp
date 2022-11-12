#pragma once

#include "Test.hpp"

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"

#include <memory>

namespace test
{
    class TestBatch2D : public Test
    {
    private:
        glm::vec3 m_translation;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;

        glm::mat4 m_Proj, m_View;

    public:
        TestBatch2D();
        ~TestBatch2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };    
    
} // namespace test
