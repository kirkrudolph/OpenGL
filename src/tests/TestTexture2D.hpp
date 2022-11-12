#pragma once

#include "Test.hpp"

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"

#include <memory>

namespace test
{
    class TestTexture2D : public Test
    {
    private:
        glm::vec3 m_translationA, m_translationB;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj, m_View;

    public:
        TestTexture2D();
        ~TestTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };    
    
} // namespace test
