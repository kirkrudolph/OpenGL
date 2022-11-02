#include "TestClearColor.hpp"

#include "Renderer.hpp"
#include "imgui-1.88/imgui.h"

namespace test {

    TestClearColor::TestClearColor(/* args */)
        : m_ClearColor {0.2f, 0.3f, 0.8f, 1.0f}
    {
    }

    TestClearColor::~TestClearColor()
    {
    }

    void TestClearColor::OnUpdate(float deltaTime){

    }

    void TestClearColor::OnRender(){
        GLCALL(glClearColor(m_ClearColor[0],m_ClearColor[1],m_ClearColor[2],m_ClearColor[3]));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::OnImguiRender(){
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
}